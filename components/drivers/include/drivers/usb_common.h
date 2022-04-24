/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2013-04-26     aozima       add DEVICEQUALIFIER support.
 * 2017-11-15     ZYH          fix ep0 transform error
 */

#ifndef __USB_COMMON_H__
#define __USB_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

#define RT_DEBUG_USB                    0x00
#define USB_DYNAMIC                     0x00

#define USB_CLASS_DEVICE                0x00
#define USB_CLASS_AUDIO                 0x01
#define USB_CLASS_CDC                   0x02
#define USB_CLASS_HID                   0x03
#define USB_CLASS_PHYSICAL              0x05
#define USB_CLASS_IMAGE                 0x06
#define USB_CLASS_PRINTER               0x07
#define USB_CLASS_MASS_STORAGE          0x08
#define USB_CLASS_HUB                   0x09
#define USB_CLASS_CDC_DATA              0x0a
#define USB_CLASS_SMART_CARD            0x0b
#define USB_CLASS_SECURITY              0x0d
#define USB_CLASS_VIDEO                 0x0e
#define USB_CLASS_HEALTHCARE            0x0f
#define USB_CLASS_DIAG_DEVICE           0xdc
#define USB_CLASS_WIRELESS              0xe0
#define USB_CLASS_MISC                  0xef
#define USB_CLASS_APP_SPECIFIC          0xfe
#define USB_CLASS_VEND_SPECIFIC         0xff

#define USB_DESC_TYPE_DEVICE            0x01
#define USB_DESC_TYPE_CONFIGURATION     0x02
#define USB_DESC_TYPE_STRING            0x03
#define USB_DESC_TYPE_INTERFACE         0x04
#define USB_DESC_TYPE_ENDPOINT          0x05
#define USB_DESC_TYPE_DEVICEQUALIFIER   0x06
#define USB_DESC_TYPE_OTHERSPEED        0x07
#define USB_DESC_TYPE_IAD               0x0b
#define USB_DESC_TYPE_HID               0x21
#define USB_DESC_TYPE_REPORT            0x22
#define USB_DESC_TYPE_PHYSICAL          0x23
#define USB_DESC_TYPE_HUB               0x29

#define USB_DESC_LENGTH_DEVICE          0x12
#define USB_DESC_LENGTH_CONFIG          0x9
#define USB_DESC_LENGTH_IAD             0x8
#define USB_DESC_LENGTH_STRING          0x4
#define USB_DESC_LENGTH_INTERFACE       0x9
#define USB_DESC_LENGTH_ENDPOINT        0x7

#define USB_REQ_TYPE_STANDARD           0x00
#define USB_REQ_TYPE_CLASS              0x20
#define USB_REQ_TYPE_VENDOR             0x40
#define USB_REQ_TYPE_MASK               0x60

#define USB_REQ_TYPE_DIR_OUT            0x00
#define USB_REQ_TYPE_DIR_IN             0x80

#define USB_REQ_TYPE_DEVICE             0x00
#define USB_REQ_TYPE_INTERFACE          0x01
#define USB_REQ_TYPE_ENDPOINT           0x02
#define USB_REQ_TYPE_OTHER              0x03
#define USB_REQ_TYPE_RECIPIENT_MASK     0x1f

#define USB_FEATURE_ENDPOINT_HALT       0x00
#define USB_FEATURE_DEV_REMOTE_WAKEUP   0x01
#define USB_FEATURE_TEST_MODE           0x02

#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME             0x0C
#define USB_REQ_SET_ENCRYPTION          0x0D
#define USB_REQ_GET_ENCRYPTION          0x0E
#define USB_REQ_RPIPE_ABORT             0x0E
#define USB_REQ_SET_HANDSHAKE           0x0F
#define USB_REQ_RPIPE_RESET             0x0F
#define USB_REQ_GET_HANDSHAKE           0x10
#define USB_REQ_SET_CONNECTION          0x11
#define USB_REQ_SET_SECURITY_DATA       0x12
#define USB_REQ_GET_SECURITY_DATA       0x13
#define USB_REQ_SET_WUSB_DATA           0x14
#define USB_REQ_LOOPBACK_DATA_WRITE     0x15
#define USB_REQ_LOOPBACK_DATA_READ      0x16
#define USB_REQ_SET_INTERFACE_DS        0x17

#define USB_STRING_LANGID_INDEX         0x00
#define USB_STRING_MANU_INDEX           0x01
#define USB_STRING_PRODUCT_INDEX        0x02
#define USB_STRING_SERIAL_INDEX         0x03
#define USB_STRING_CONFIG_INDEX         0x04
#define USB_STRING_INTERFACE_INDEX      0x05
#define USB_STRING_OS_INDEX             0x06
#define USB_STRING_MAX                  0xff

#define USB_STRING_OS                   "MSFT100A"

#define USB_PID_OUT                     0x01
#define USB_PID_ACK                     0x02
#define USB_PID_DATA0                   0x03
#define USB_PID_SOF                     0x05
#define USB_PID_IN                      0x09
#define USB_PID_NACK                    0x0A
#define USB_PID_DATA1                   0x0B
#define USB_PID_PRE                     0x0C
#define USB_PID_SETUP                   0x0D
#define USB_PID_STALL                   0x0E

#define USB_EP_DESC_OUT                 0x00
#define USB_EP_DESC_IN                  0x80
#define USB_EP_DESC_NUM_MASK            0x0f

#define USB_EP_ATTR_CONTROL             0x00
#define USB_EP_ATTR_ISOC                0x01
#define USB_EP_ATTR_BULK                0x02
#define USB_EP_ATTR_INT                 0x03
#define USB_EP_ATTR_TYPE_MASK           0x03

#define USB_EPNO_MASK                   0x7f
#define USB_DIR_OUT                     0x00
#define USB_DIR_IN                      0x80
#define USB_DIR_INOUT                   0x40
#define USB_DIR_MASK                    0x80

#define ID_UNASSIGNED                   0
#define ID_ASSIGNED                     1

#define RH_GET_PORT_STATUS              0
#define RH_SET_PORT_STATUS              1
#define RH_CLEAR_PORT_FEATURE           2
#define RH_SET_PORT_FEATURE             3

#define USB_BUS_POWERED                 0
#define USB_SELF_POWERED                1
#define USB_REMOTE_WAKEUP               1
#define USB_EP_HALT                     0

/*
 * Port feature numbers
 */
#define PORT_FEAT_CONNECTION            0
#define PORT_FEAT_ENABLE                1
#define PORT_FEAT_SUSPEND               2
#define PORT_FEAT_OVER_CURRENT          3
#define PORT_FEAT_RESET                 4
#define PORT_FEAT_POWER                 8
#define PORT_FEAT_LOWSPEED              9
#define PORT_FEAT_HIGHSPEED             10
#define PORT_FEAT_C_CONNECTION          16
#define PORT_FEAT_C_ENABLE              17
#define PORT_FEAT_C_SUSPEND             18
#define PORT_FEAT_C_OVER_CURRENT        19
#define PORT_FEAT_C_RESET               20

/*
    The HcRhPortStatus[1:NDP] register is used to control and report port events on a per-port
    basis. NumberDownstreamPorts represents the number of HcRhPortStatus registers that are
    implemented in hardware.  The lower word is used to reflect the port status, whereas the upper
    word reflects the status change bits.  Some status bits are implemented with special write behavior
    (see below).  If a transaction (token through handshake) is in progress when a write to change
    port status occurs, the resulting port status change must be postponed until the transaction
    completes.  Reserved bits should always be written '0'.
*/
#define PORT_CCS                        0x00000001UL    /* R:CurrentConnectStatus - W:ClearPortEnable    */
#define PORT_PES                        0x00000002UL    /* R:PortEnableStatus - W:SetPortEnable             */
#define PORT_PSS                        0x00000004UL    /* R:PortSuspendStatus - W:SetPortSuspend        */
#define PORT_POCI                       0x00000008UL    /* R:PortOverCurrentIndicator - W:ClearSuspendStatus    */
#define PORT_PRS                        0x00000010UL    /* R:PortResetStatus - W: SetPortReset            */
#define PORT_PPS                        0x00000100UL    /* R:PortPowerStatus - W: SetPortPower            */
#define PORT_LSDA                       0x00000200UL    /* R:LowSpeedDeviceAttached - W:ClearPortPower    */
#define PORT_CCSC                       0x00010000UL
#define PORT_PESC                       0x00020000UL
#define PORT_PSSC                       0x00040000UL
#define PORT_POCIC                      0x00080000UL
#define PORT_PRSC                       0x00100000UL

/*
 *Hub Status & Hub Change bit masks
 */
#define HUB_STATUS_LOCAL_POWER          0x0001
#define HUB_STATUS_OVERCURRENT          0x0002

#define HUB_CHANGE_LOCAL_POWER          0x0001
#define HUB_CHANGE_OVERCURRENT          0x0002

#define USB_EP_ATTR(attr)               (attr & USB_EP_ATTR_TYPE_MASK)
#define USB_EP_DESC_NUM(addr)           (addr & USB_EP_DESC_NUM_MASK)
#define USB_EP_DIR(addr)                ((addr & USB_DIR_MASK)>>7)

#define HID_REPORT_ID_KEYBOARD1         1
#define HID_REPORT_ID_KEYBOARD2         2
#define HID_REPORT_ID_KEYBOARD3         3
#define HID_REPORT_ID_KEYBOARD4         7
#define HID_REPORT_ID_MEDIA             4
#define HID_REPORT_ID_GENERAL           5
#define HID_REPORT_ID_MOUSE             6

/*
 * Time of usb timeout
 */
#ifndef USB_TIMEOUT_BASIC
#define USB_TIMEOUT_BASIC               (RT_TICK_PER_SECOND)        /* 1s */
#endif
#ifndef USB_TIMEOUT_LONG
#define USB_TIMEOUT_LONG                (RT_TICK_PER_SECOND * 5)    /* 5s */
#endif
#ifndef USB_DEBOUNCE_TIME
#define USB_DEBOUNCE_TIME               (RT_TICK_PER_SECOND / 5)    /* 0.2s */
#endif

#define uswap_32(x) \
    ((((x) & 0xff000000) >> 24) | \
     (((x) & 0x00ff0000) >>  8) | \
     (((x) & 0x0000ff00) <<  8) | \
     (((x) & 0x000000ff) << 24))

#define  uswap_8(x) \
    (((rt_uint16_t)(*((rt_uint8_t *)(x)))) + \
    (((rt_uint16_t)(*(((rt_uint8_t *)(x)) + 1))) << 8))

typedef void (*func_callback)(void *context);
typedef enum
{
    USB_STATE_NOTATTACHED = 0,
    USB_STATE_ATTACHED,
    USB_STATE_POWERED,
    USB_STATE_RECONNECTING,
    USB_STATE_UNAUTHENTICATED,
    USB_STATE_DEFAULT,
    USB_STATE_ADDRESS,
    USB_STATE_CONFIGURED,
    USB_STATE_SUSPENDED
}udevice_state_t;

typedef enum
{
    STAGE_IDLE,
    STAGE_SETUP,
    STAGE_STATUS_IN,
    STAGE_STATUS_OUT,
    STAGE_DIN,
    STAGE_DOUT
} uep0_stage_t;

#pragma pack(1)

struct usb_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
};
typedef struct usb_descriptor* udesc_t;

struct udevice_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint16_t bcdUSB;
    rt_uint8_t bDeviceClass;
    rt_uint8_t bDeviceSubClass;
    rt_uint8_t bDeviceProtocol;
    rt_uint8_t bMaxPacketSize0;
    rt_uint16_t idVendor;
    rt_uint16_t idProduct;
    rt_uint16_t bcdDevice;
    rt_uint8_t iManufacturer;
    rt_uint8_t iProduct;
    rt_uint8_t iSerialNumber;
    rt_uint8_t bNumConfigurations;
};
typedef struct udevice_descriptor* udev_desc_t;

struct uconfig_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint16_t wTotalLength;
    rt_uint8_t bNumInterfaces;
    rt_uint8_t bConfigurationValue;
    rt_uint8_t iConfiguration;
    rt_uint8_t bmAttributes;
    rt_uint8_t MaxPower;
    rt_uint8_t data[2048];
};
typedef struct uconfig_descriptor* ucfg_desc_t;

struct uinterface_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint8_t bInterfaceNumber;
    rt_uint8_t bAlternateSetting;
    rt_uint8_t bNumEndpoints;
    rt_uint8_t bInterfaceClass;
    rt_uint8_t bInterfaceSubClass;
    rt_uint8_t bInterfaceProtocol;
    rt_uint8_t iInterface;
};
typedef struct uinterface_descriptor* uintf_desc_t;

/* Interface Association Descriptor (IAD) */
struct uiad_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t bDescriptorType;
    rt_uint8_t bFirstInterface;
    rt_uint8_t bInterfaceCount;
    rt_uint8_t bFunctionClass;
    rt_uint8_t bFunctionSubClass;
    rt_uint8_t bFunctionProtocol;
    rt_uint8_t iFunction;
};
typedef struct uiad_descriptor* uiad_desc_t;

struct uendpoint_descriptor
{
    rt_uint8_t  bLength;
    rt_uint8_t  type;
    rt_uint8_t  bEndpointAddress;
    rt_uint8_t  bmAttributes;
    rt_uint16_t wMaxPacketSize;
    rt_uint8_t  bInterval;
};
typedef struct uendpoint_descriptor* uep_desc_t;

struct ustring_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint8_t String[64];
};
typedef struct ustring_descriptor* ustr_desc_t;

struct uhub_descriptor
{
    rt_uint8_t length;
    rt_uint8_t type;
    rt_uint8_t num_ports;
    rt_uint16_t characteristics;
    rt_uint8_t pwron_to_good;        /* power on to power good */
    rt_uint8_t current;
    rt_uint8_t removable[8];
    rt_uint8_t pwr_ctl[8];
};
typedef struct uhub_descriptor* uhub_desc_t;

/* USB_DESC_TYPE_DEVICEQUALIFIER: Device Qualifier descriptor */
struct usb_qualifier_descriptor
{
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;

    rt_uint16_t bcdUSB; // TODO: big-endian.
    rt_uint8_t  bDeviceClass;
    rt_uint8_t  bDeviceSubClass;
    rt_uint8_t  bDeviceProtocol;
    rt_uint8_t  bMaxPacketSize0;
    rt_uint8_t  bNumConfigurations;
    rt_uint8_t  bRESERVED;
} __attribute__ ((packed));

struct usb_os_header_comp_id_descriptor
{
    rt_uint32_t dwLength;
    rt_uint16_t bcdVersion;
    rt_uint16_t wIndex;
    rt_uint8_t  bCount;
    rt_uint8_t  reserved[7];
};
typedef struct usb_os_header_comp_id_descriptor * usb_os_header_desc_t;

struct usb_os_property_header
{
    rt_uint32_t dwLength;
    rt_uint16_t bcdVersion;
    rt_uint16_t wIndex;
    rt_uint16_t wCount;
};
typedef struct usb_os_property_header * usb_os_property_header_t;
struct usb_os_proerty
{
    rt_uint32_t dwSize;
    rt_uint32_t dwPropertyDataType;
    rt_uint16_t wPropertyNameLength;
    const char * bPropertyName;
    rt_uint32_t dwPropertyDataLength;
    const char * bPropertyData;
};
typedef struct usb_os_proerty * usb_os_proerty_t;

// Value    Description
//  1       A NULL-terminated Unicode String (REG_SZ)
//  2       A NULL-terminated Unicode String that includes environment variables (REG_EXPAND_SZ)
//  3       Free-form binary (REG_BINARY)
//  4       A little-endian 32-bit integer (REG_DWORD_LITTLE_ENDIAN)
//  5       A big-endian 32-bit integer (REG_DWORD_BIG_ENDIAN)
//  6       A NULL-terminated Unicode string that contains a symbolic link (REG_LINK)
//  7       Multiple NULL-terminated Unicode strings (REG_MULTI_SZ)
#define USB_OS_PROPERTY_TYPE_REG_SZ                      0x01UL
#define USB_OS_PROPERTY_TYPE_REG_EXPAND_SZ               0x02UL
#define USB_OS_PROPERTY_TYPE_REG_BINARY                  0x03UL
#define USB_OS_PROPERTY_TYPE_REG_DWORD_LITTLE_ENDIAN     0x04UL
#define USB_OS_PROPERTY_TYPE_REG_DWORD_BIG_ENDIAN        0x05UL
#define USB_OS_PROPERTY_TYPE_REG_LINK                    0x06UL
#define USB_OS_PROPERTY_TYPE_REG_MULTI_SZ                0x07UL

#define USB_OS_PROPERTY_DESC(PropertyDataType,PropertyName,PropertyData) \
{\
    .dwSize                 = sizeof(struct usb_os_proerty)-sizeof(const char *)*2\
                            +sizeof(PropertyName)*2+sizeof(PropertyData)*2,\
    .dwPropertyDataType     = PropertyDataType,\
    .wPropertyNameLength    = sizeof(PropertyName)*2,\
    .bPropertyName          = PropertyName,\
    .dwPropertyDataLength   = sizeof(PropertyData)*2,\
    .bPropertyData          = PropertyData\
}


#ifndef HID_SUB_DESCRIPTOR_MAX
#define  HID_SUB_DESCRIPTOR_MAX        1
#endif

struct uhid_descriptor
{
    rt_uint8_t  bLength;
    rt_uint8_t  type;
    rt_uint16_t bcdHID;
    rt_uint8_t  bCountryCode;
    rt_uint8_t  bNumDescriptors;
    struct hid_descriptor_list
    {
        rt_uint8_t type;
        rt_uint16_t wLength;
    }Descriptor[HID_SUB_DESCRIPTOR_MAX];
};
typedef struct uhid_descriptor* uhid_desc_t;

struct hid_report
{
    rt_uint8_t report_id;
    rt_uint8_t report[63];
    rt_uint8_t size;
};
typedef struct hid_report* hid_report_t;
extern void HID_Report_Received(hid_report_t report);

struct urequest
{
    rt_uint8_t  request_type;
    rt_uint8_t  bRequest;
    rt_uint16_t wValue;
    rt_uint16_t wIndex;
    rt_uint16_t wLength;
};
typedef struct urequest* ureq_t;

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif
#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif

/*
 * the define related to mass storage
 */
#define USBREQ_GET_MAX_LUN              0xfe
#define USBREQ_MASS_STORAGE_RESET       0xff

#define SIZEOF_CSW                      0x0d
#define SIZEOF_CBW                      0x1f
#define SIZEOF_INQUIRY_CMD              0x24
#define SIZEOF_MODE_SENSE_6             0x4
#define SIZEOF_READ_CAPACITIES          0xc
#define SIZEOF_READ_CAPACITY            0x8
#define SIZEOF_REQUEST_SENSE            0x12

#define CBWFLAGS_DIR_M                  0x80
#define CBWFLAGS_DIR_IN                 0x80
#define CBWFLAGS_DIR_OUT                0x00

#define SCSI_TEST_UNIT_READY            0x00
#define SCSI_REQUEST_SENSE              0x03
#define SCSI_INQUIRY_CMD                0x12
#define SCSI_ALLOW_REMOVAL              0x1e
#define SCSI_MODE_SENSE_6               0x1a
#define SCSI_START_STOP                 0x1b
#define SCSI_READ_CAPACITIES            0x23
#define SCSI_READ_CAPACITY              0x25
#define SCSI_READ_10                    0x28
#define SCSI_WRITE_10                   0x2a
#define SCSI_VERIFY_10                  0x2f

#define CBW_SIGNATURE                   0x43425355
#define CSW_SIGNATURE                   0x53425355
#define CBW_TAG_VALUE                   0x12345678

struct ustorage_cbw
{
    rt_uint32_t signature;
    rt_uint32_t tag;
    rt_uint32_t xfer_len;
    rt_uint8_t dflags;
    rt_uint8_t lun;
    rt_uint8_t cb_len;
    rt_uint8_t cb[16];
};
typedef struct ustorage_cbw* ustorage_cbw_t;

struct ustorage_csw
{
    rt_uint32_t signature;
    rt_uint32_t tag;
    rt_int32_t data_reside;
    rt_uint8_t  status;
};
typedef struct ustorage_csw* ustorage_csw_t;

#pragma pack()

struct usb_os_comp_id_descriptor
{
    struct usb_os_header_comp_id_descriptor head_desc;
    rt_list_t func_desc;
};
typedef struct usb_os_comp_id_descriptor * usb_os_comp_id_desc_t;

struct usb_os_function_comp_id_descriptor
{
    rt_list_t list;
    rt_uint8_t bFirstInterfaceNumber;
    rt_uint8_t reserved1;
    rt_uint8_t compatibleID[8];
    rt_uint8_t subCompatibleID[8];
    rt_uint8_t reserved2[6];
};
typedef struct usb_os_function_comp_id_descriptor * usb_os_func_comp_id_desc_t;

/*
 * USB device event loop thread configurations
 */
/* the stack size of USB thread */
#ifndef RT_USBD_THREAD_STACK_SZ
#define RT_USBD_THREAD_STACK_SZ 512
#endif

/* the priority of USB thread */
#ifndef RT_USBD_THREAD_PRIO
#define RT_USBD_THREAD_PRIO 8
#endif


#ifdef __cplusplus
}
#endif

#endif
