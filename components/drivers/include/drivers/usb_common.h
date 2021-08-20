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
#include <uapi/usb/ch9.h>

#define RT_DEBUG_USB                    0x00
#define USB_DYNAMIC                     0x00

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

#define ID_UNASSIGNED                   0
#define ID_ASSIGNED                     1


/*
    The HcRhPortStatus[1:NDP] register is used to control and report port events on a per-port
    basis. NumberDownstreamPorts represents the number of HcRhPortStatus registers that are
    implemented in hardware.  The lower word is used to reflect the port status, whereas the upper
    word reflects the status change bits.  Some status bits are implemented with special write behavior
    (see below).  If a transaction (token through handshake) is in progress when a write to change
    port status occurs, the resulting port status change must be postponed until the transaction
    completes.  Reserved bits should always be written '0'.
*/

#define PORT_CCSC                       0x00010000UL    /* CurrentConnect ability */
#define PORT_PESC                       0x00020000UL    /* PortEnable ability */
#define PORT_PSSC                       0x00040000UL    /* PortSuspend ability */
#define PORT_POCIC                      0x00080000UL    /* PortOverCurrentIndicator ability */
#define PORT_PRSC                       0x00100000UL    /* PortReset ability */

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
    STAGE_IDLE,
    STAGE_SETUP,
    STAGE_STATUS_IN,
    STAGE_STATUS_OUT,
    STAGE_DIN,
    STAGE_DOUT
} uep0_stage_t;

#pragma pack(1)

struct usb_os_header_comp_id_descriptor
{
    rt_uint32_t dwLength;
    rt_uint16_t bcdVersion;
    rt_uint16_t wIndex;
    rt_uint8_t  bCount;
    rt_uint8_t  reserved[7];
};
typedef struct usb_os_header_comp_id_descriptor * usb_os_header_desc_t;

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

struct usb_os_comp_id_descriptor
{
    struct usb_os_header_comp_id_descriptor head_desc;
    rt_list_t func_desc;
};
typedef struct usb_os_comp_id_descriptor * usb_os_comp_id_desc_t;

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


struct hid_report
{
    rt_uint8_t report_id;
    rt_uint8_t report[63];
    rt_uint8_t size;
};
typedef struct hid_report* hid_report_t;
extern void HID_Report_Received(hid_report_t report);

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
