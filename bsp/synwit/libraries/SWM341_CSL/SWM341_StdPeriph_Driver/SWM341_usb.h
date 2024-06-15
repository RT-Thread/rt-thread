#ifndef __SWM341_USB_H__
#define __SWM341_USB_H__

#include <stdint.h>


typedef struct {
    uint8_t  bRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} USB_Setup_Packet_t;


/* bRequestType D7 Data Phase Transfer Direction  */
#define  USB_REQ_DIR_MASK           0x80
#define  USB_REQ_H2D                0x00
#define  USB_REQ_D2H                0x80

/* bRequestType D6..5 Type */
#define  USB_REQ_STANDARD           0x00
#define  USB_REQ_CLASS              0x20
#define  USB_REQ_VENDOR             0x40

/* bRequestType D4..0 Recipient */
#define  USB_REQ_TO_DEVICE          0x00
#define  USB_REQ_TO_INTERFACE       0x01
#define  USB_REQ_TO_ENDPOINT        0x02

/* USB Standard Request */
#define USB_GET_STATUS              0x00
#define USB_CLEAR_FEATURE           0x01
#define USB_SET_FEATURE             0x03
#define USB_SET_ADDRESS             0x05
#define USB_GET_DESCRIPTOR          0x06
#define USB_SET_DESCRIPTOR          0x07
#define USB_GET_CONFIGURATION       0x08
#define USB_SET_CONFIGURATION       0x09
#define USB_GET_INTERFACE           0x0A
#define USB_SET_INTERFACE           0x0B
#define USB_SYNC_FRAME              0x0C

/* USB Descriptor Type */
#define USB_DESC_DEVICE             0x01
#define USB_DESC_CONFIG             0x02
#define USB_DESC_STRING             0x03
#define USB_DESC_INTERFACE          0x04
#define USB_DESC_ENDPOINT           0x05
#define USB_DESC_QUALIFIER          0x06
#define USB_DESC_OTHERSPEED         0x07
#define USB_DESC_IFPOWER            0x08
#define USB_DESC_OTG                0x09
#define USB_DESC_BOS                0x0F
#define USB_DESC_CAPABILITY         0x10
#define USB_DESC_CS_INTERFACE       0x24    // Class Specific Interface

/* USB HID Descriptor Type */
#define USB_DESC_HID                0x21
#define USB_DESC_HID_RPT            0x22

/* USB Endpoint Type */
#define USB_EP_CTRL                 0x00
#define USB_EP_ISO                  0x01
#define USB_EP_BULK                 0x02
#define USB_EP_INT                  0x03

#define USB_EP_IN                   0x80
#define USB_EP_OUT                  0x00

/* USB Feature Selector */
#define USB_FEATURE_REMOTE_WAKEUP   0x01
#define USB_FEATURE_ENDPOINT_HALT   0x00

/* USB HID Class Report Type */
#define HID_RPT_TYPE_INPUT          0x01
#define HID_RPT_TYPE_OUTPUT         0x02
#define HID_RPT_TYPE_FEATURE        0x03

/* Define HID Class Specific Request */
#define USB_HID_GET_REPORT          0x01
#define USB_HID_GET_IDLE            0x02
#define USB_HID_GET_PROTOCOL        0x03
#define USB_HID_SET_REPORT          0x09
#define USB_HID_SET_IDLE            0x0A
#define USB_HID_SET_PROTOCOL        0x0B


/* Class */
#define USB_CDC_CLASS               0x02    // for Device
#define USB_CDC_CTRL_CLASS          0x02    // for Interface
#define USB_CDC_DATA_CLASS          0x0A    // for Interface
#define USB_HID_CLASS               0x03    // for Interface
#define USB_MTP_CLASS               0x06    // for Interface
#define USB_MSC_CLASS               0x08    // for Interface
#define USB_UVC_CLASS               0x0E    // for Interface


/* SubClass */
#define USB_CDC_ACM                 0x02    // Abstract Control Model
#define USB_HID_BOOT                0x01
#define USB_UVC_VIDEOCONTROL                0x01
#define USB_UVC_VIDEOSTREAMING              0x02
#define USB_UVC_VIDEO_INTERFACE_COLLECTION  0x03

/* Protocol */
#define USB_CDC_ATCMD               0x01    // AT Commands defined by ITU-T V.250
#define USB_HID_NONE                0x00
#define USB_HID_KEYBD               0x01
#define USB_HID_MOUSE               0x02
#define USB_MSC_BOT                 0x50    // Bulk-Only Transport


typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
} USB_DescHeader_t;

typedef struct __attribute__((packed)) {
    uint8_t   bLength;
    uint8_t   bDescriptorType;
    uint16_t  bcdUSB;               // USB Specification Number which device complies to
    uint8_t   bDeviceClass;         // 0x00: each interface specifies its own class code
    uint8_t   bDeviceSubClass;
    uint8_t   bDeviceProtocol;
    uint8_t   bMaxPacketSize;
    uint16_t  idVendor;             // Vendor ID (Assigned by USB Org)
    uint16_t  idProduct;            // Product ID (Assigned by Manufacturer)
    uint16_t  bcdDevice;            // Device Release Number
    uint8_t   iManufacturer;        // Index of Manufacturer String Descriptor
    uint8_t   iProduct;             // Index of Product String Descriptor
    uint8_t   iSerialNumber;        // Index of Serial Number String Descriptor
    uint8_t   bNumConfigurations;   // Number of Possible Configurations
} USB_DevDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t   bLength;
    uint8_t   bDescriptorType;
    uint16_t  wTotalLength;         // Total Length
    uint8_t   bNumInterfaces;       // Number of Interfaces
    uint8_t   bConfigurationValue;  // Value to use as an argument to select this configuration
    uint8_t   iConfiguration;       // Index of String Descriptor Describing this configuration
    uint8_t   bmAttributes;         // D7 Bus Powered , D6 Self Powered, D5 Remote Wakeup , D4..0 Reserved (0)
    uint8_t   bMaxPower;            // Maximum Power Consumption
} USB_CfgDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;      // Value used to select alternative setting
    uint8_t bNumEndpoints;          // Number of Endpoints used for this interface
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;             // Index of String Descriptor Describing this interface
} USB_IntfDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t   bLength;
    uint8_t   bDescriptorType;
    uint8_t   bEndpointAddress;     // indicates what endpoint this descriptor is describing
    uint8_t   bmAttributes;         // specifies the transfer type.
    uint16_t  wMaxPacketSize;       // Maximum Packet Size this endpoint is capable of sending or receiving
    uint8_t   bInterval;            // is used to specify the polling interval of certain transfers.
} USB_EpDesc_t;

typedef struct __attribute__((packed)) {
    uint8_t   bLength;
    uint8_t   bDescriptorType;
    uint16_t  bcdHID;               // indicates what endpoint this descriptor is describing
    uint8_t   bCountryCode;
    uint8_t   bNumDescriptors;
    uint8_t   bReportDescriptorType;
    uint16_t  wItemLength;
} USB_HIDDesc_t;


/* Header Functional Descriptor, which marks the beginning of the
   concatenated set of functional descriptors for the interface. */
typedef struct __attribute__((packed)) {
    uint8_t  bLength;
    uint8_t  bDescriptorType;       // CS_INTERFACE (0x24)
    uint8_t  bDescriptorSubType;    // 0x00
    uint16_t bcdCDC;
} USB_CDC_HeaderFuncDesc_t;


/* Call Management Functional Descriptor */
typedef struct __attribute__((packed)) {
    uint8_t  bLength;
    uint8_t  bDescriptorType;       // CS_INTERFACE (0x24)
    uint8_t  bDescriptorSubType;    // 0x01
    uint8_t  bmCapabilities;
    uint8_t  bDataInterface;
} USB_CDC_CallMgmtFuncDesc_t;


/* Abstract Control Management Functional Descriptor */
typedef struct __attribute__((packed)) {
    uint8_t  bLength;
    uint8_t  bDescriptorType;       // CS_INTERFACE (0x24)
    uint8_t  bDescriptorSubType;    // 0x02
    uint8_t  bmCapabilities;
} USB_CDC_AbstCntrlMgmtFuncDesc_t;


/* Union Functional Descriptor */
typedef struct __attribute__((packed)) {
    uint8_t  bLength;
    uint8_t  bDescriptorType;       // CS_INTERFACE (0x24)
    uint8_t  bDescriptorSubType;    // 0x06
    uint8_t  bMasterInterface;      // Interface number of the Communication or Data Class interface
    uint8_t  bSlaveInterface0;      // Interface number of first slave
} USB_CDC_UnionFuncDesc_t;


#endif //__SWM341_USB_H__
