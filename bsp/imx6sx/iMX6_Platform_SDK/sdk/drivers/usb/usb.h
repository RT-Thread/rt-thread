/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * File:		USB.h
 * Purpose:		USB definitions
 *
 * Notes:
 */

#ifndef _USB_H
#define _USB_H

#include "usb_defines.h"
#include "usb_registers.h"

//! @brief    USB cores for mx6dq/mx6dl
enum usbController {
    OTG = 0,
    Host1,
    Host2,
    Host3,
    OTG1,
    OTG2,
    HOST,
};

//! @brief    USB phy types	
enum usbPhyType {
    Utmi,	//! USB Transceiver Macrocell Interface 
    Ulpi,	//! UTMI+ low pin interface
    Serial,	//! Serial interface
    Hsic	//! High-Speed Inter-Chip
};

//! @brief   USB bus speeds 
typedef enum usbPortSpeed {
    usbSpeedFull,	//! Full speed, 12MHz
    usbSpeedLow,	//! Low speed
    usbSpeedHigh,	//! High speed, 480MHz
    usbSpeedUnknown,
} usbPortSpeed_t;

//! @brief    the types of usb periodic list
typedef enum usbPeriodicListType {
    listTypeIsochronous = 0,	//! Isochronous Transfer
    listTypeQueueHead,		//! Queue Head
    listTypeSplitTransaction, 	//! Split Transaction Isochronous Transfer
    listTypeFrameSpan		//! Periodic Frame Span Traversal Node
} usbPeriodicListType_t;

//! @brief    the data structure for USB core
typedef struct usb_module {
    char *moduleName;
    enum usbController controllerID;	//! USB Core used 
    enum usbPhyType phyType;    // UTMI, ULPI, Serial, HSIC
} usb_module_t;

/*!
 *  usb host data structure definitions
 */

/* USB host queue head structure */
typedef struct usbhQueueHead {
    uint32_t queueHeadLinkPointer;	//! Queue Head Horizontal Link Pointer
    uint32_t endpointCharacteristics;	//! Characteristics
    uint32_t endpointCapabilities;	//! Capabilities
    uint32_t currentQtd;		//! Current qTD Pointer
    uint32_t nextQtd;			//! Next qTD Pointer
    uint32_t alternateNextQtd;		//! Alternate Next qTD pointer
    uint32_t qtdToken;			//! Token
    uint32_t qtdBuffer[5];		//! Buffer Pointers
    uint32_t mallocPointer;     /* Used to keep track of the
                                   memory block allocated for the data structure */
} usbhQueueHead_t;

/*!
 *  USB host queue element transfer descriptor
 */
typedef struct usbhTransferDescriptor {
    uint32_t nextQtd;		//! Next qTD Pointer
    uint32_t alternateNextQtd;	//! Alternate Next qTD Pointer
    uint32_t qtdToken;		//! Token
    uint32_t qtdBuffer[5];	//! Buffer Pointers
    uint32_t mallocPointer;     /* Used to keep track of the unaligned
                                   memory allocated for the data structure */

} usbhTransferDescriptor_t;

/*!
 * Protocol descriptor definitions, pleeae refer USB specification 2.0 for details.
 */
typedef struct usbDeviceDescriptor {
    uint8_t bLength;		//! Size of this descriptor in bytes
    uint8_t bDescriptorType;	//! DEVICE Descriptor Type
    uint16_t bcdUSB;		//! USB Specification Release Number
    uint8_t bDeviceClass;	//! Class code
    uint8_t bDeviceSubClass;	//! Subclass code
    uint8_t bDeviceProtocol;	//! Protocol code
    uint8_t bMaxPacketSize;	//! Maximum packet size for endpoint zero
    uint16_t idVendor;          //! Vendor ID
    uint16_t idProduct;         //! Product ID
    uint16_t bcdDevice;         //! Device release number
    uint8_t iManufacturer;      //! Index of string descriptor describing manufacturer
    uint8_t iProduct;           //! Index of string descriptor describing product
    uint8_t iSerialNumber; 	//! Index of string descriptor describing the device's serial number
    uint8_t bNumConfigurations; //! Number of possible configurations
}  __attribute__ ((packed)) usbDeviceDescriptor_t;

typedef struct usbConfigurationDescriptor {
    uint8_t bLength;			//! Size of descriptor	
    uint8_t bDescriptorType;		//! CONFIGURATION Descriptor Type
    uint16_t wTotalLength;              //! Total length of data returned for this configuration
    uint8_t bNumInterfaces;             //! Number of interfaces supported by this configuration
    uint8_t bConfigurationValue;        //! Value to use as an argument to the to select this configuration
    uint8_t iConfiguration;             //! Index of string descriptor describing this configuration
    uint8_t bmAttributes;		//! Configuration characteristics
    uint8_t MaxPower;			//! Maximum power consumption of the USB device
}  __attribute__ ((packed)) usbConfigurationDescriptor_t;

typedef struct usbInterfaceDescriptor {
    uint8_t bLength;		//! Size of this descriptor in bytes 
    uint8_t bDescriptorType;    //! INTERFACE Descriptor Type
    uint8_t bInterfaceNumber;   //! Number of this interface
    uint8_t bAlternateSetting;  //! Value used to select this alternate setting
    uint8_t bNumEndpoints;      //! Number of endpoints used by this interface
    uint8_t bInterfaceClass;    //! Class code
    uint8_t bInterfaceSubClass; //! Subclass code
    uint8_t bInterfaceProtocol; //! Protocol code
    uint8_t iInterface;		//! Index of string descriptor describing this interface
}  __attribute__ ((packed)) usbInterfaceDescriptor_t;

/* USB Descriptor Types */
#define DEVICE_DESCRIPTOR             0x1	//! Type for Device Descriptor
#define CONFIG_DESCRIPTOR             0x2	//! Type for Configuration Descriptor 
#define STRING_DESCRIPTOR             0x3	//! Type for String Descriptor
#define INTERFACE_DESCRIPTOR          0x4       //! Type for interface Descriptor
#define ENDPOINT_DESCRIPTOR           0x5	//! Type for endpoint Descriptor
#define DEVICE_QUALIFIER_DESCRIPTOR   0x6       //! Type for device qualifier descriptor
#define OTHER_SPEED_CONFIG_DESCRIPTOR 0x7	//! Type for other speed configuration descriptor
#define INTERFACE_POWER_DESCRIPTOR    0x8	//! Type for  interface power descriptor

//HID class interface descriptor definitions
#define CLASS_CODE_HID                     0x03	//! Class code for HID 
#define SUBCLASS_CODE_HID_NOSUBCLASS       0x00	//! Subclass code
#define SUBCLASS_CODE_HID_BOOT_INTERFACE   0x01	//! Subcalss code
#define PROTOCOL_CODE_HID_NONE             0x00 //!
#define PROTOCOL_CODE_HID_KEYBOARD         0x01 //! HID protocol code: Keyboard
#define PROTOCOL_CODE_HID_MOUSE            0x02 //! HID protocol code: Mouse

//MSC class interface descriptor definitions
#define CLASS_CODE_MSC                     0x08
#define SUBCLASS_CODE_MSC_RBC              0x01 /*Reduced Block Commandds, typically for a flash device */
#define SUBCLASS_CODE_MSC_SFF8020          0x02 /*a CD/DVD device uses SFF-8020i or MMC-2 command blocks */
#define SUBCLASS_CODE_MSC_QIC              0x03 /*a tape device uses QIC-157 command blocks */
#define SUBCLASS_CODE_MSC_UFI              0x04 /*a floppy disk drive device */
#define SUBCLASS_CODE_MSC_SFF8070          0x05 /*a floppy disk drive device */
#define SUBCLASS_CODE_MSC_SCSI             0x06 /*SCSI transparent command set, popular in msc */
#define PROTOCOL_CODE_MSC_CBI00            0x00 /*for floppy device - with command completion interrupt */
#define PROTOCOL_CODE_MSC_CBI01            0x01 /*for floppy device - with no command completion interrupt */
#define PROTOCOL_CODE_MSC_BOT              0x50 /*Bulk-Only Transport, popular in msc */

//HUB class interface descriptor definitions
#define CLASS_CODE_HUB                     0x09	//! Class code for HUB
#define SUBCLASS_CODE_HUB                  0x00	//! Subclass code for HUB
#define PROTOCOL_CODE_HUB_NON_HIGHSPEED    0x00 /*for full/low speed hub */
#define PROTOCOL_CODE_HUB_MULTI_TT         0x02 /*multiple TT */
#define PROTOCOL_CODE_USB_SINGLE_TT        0x01 /*single TT */

typedef struct usbEndpointDescriptor {
    uint8_t bLength;		//! Size of this descriptor in bytes 
    uint8_t bDescriptorType;    //! ENDPOINT Descriptor Type
    uint8_t bEndpointAddress;   //! The address of the endpoint on the USB device described by this descriptor
    uint8_t bmAttributes;       //! The endpoint'ss attributes
    uint16_t wMaxPacketSize;    //! Maximum packet size
    uint8_t bInterval;          //! Interval for polling endpoint for data transfers
}  __attribute__ ((packed)) usbEndpointDescriptor_t;

typedef struct usbHidDescriptor {
    uint8_t bLength;			//! Size of this descriptor in bytes 
    uint8_t bDescriptorType;            //! Descriptor Type
    uint16_t bcdHID;                    //! Release number
    uint8_t bCountryCode;               //! Country code
    uint8_t bNumDescriptors;            //! Number of descriptors
    uint8_t bReportDescriptorType;      //! The type of report descriptor
    uint8_t wDescriptorLength[2];   // !!!! Not aligned on 16-bit boundary  !!!
}  __attribute__ ((packed)) usbHidDescriptor_t;

// USB HUB class-specific descriptor
typedef struct usb_hub_descriptor {
    uint8_t bLength;                 //Number of bytes in this descriptor
    uint8_t bDescriptorType;         //Descriptor type, must be 29H
    uint8_t bNbrPorts;               //Number of downstream ports supported by this hub
    uint8_t bHubCharacteristics[2];  //Characteristics of this hub
    uint8_t bPwrOn2PwrGood;          //Time(in 2ms intervals) from the time the power-on sequence begins
                                     //  on a port until power is good on that port
    uint8_t bHubContrCurrent;        //maximum current requirements of the hub controller electronics in mA
    uint8_t DeviceRemovable;         //indicates if a port has a removable device attached
} __attribute__ ((packed)) usb_hub_descriptor_t;

/* HUB Class Feature Selctor Table 11-17*/
#define HUB_CLASS_FEATURE_SELECTOR_C_HUB_LOCAL_POWER            0
#define HUB_CLASS_FEATURE_SELECTOR_C_HUB_OVER_CURRENT           1

#define HUB_CLASS_FEATURE_SELECTOR_PORT_CONNECTION              0
#define HUB_CLASS_FEATURE_SELECTOR_PORT_ENABLE                  1
#define HUB_CLASS_FEATURE_SELECTOR_PORT_SUSPEND                 2
#define HUB_CLASS_FEATURE_SELECTOR_PORT_OVER_CURRENT            3
#define HUB_CLASS_FEATURE_SELECTOR_PORT_RESET                   4
#define HUB_CLASS_FEATURE_SELECTOR_PORT_POWER                   8
#define HUB_CLASS_FEATURE_SELECTOR_PORT_LOW_SPEED               9

#define HUB_CLASS_FEATURE_SELECTOR_C_PORT_CONNECTION            16
#define HUB_CLASS_FEATURE_SELECTOR_C_PORT_ENABLE                17
#define HUB_CLASS_FEATURE_SELECTOR_C_PORT_SUSPEND               18
#define HUB_CLASS_FEATURE_SELECTOR_C_PORT_OVER_CURRENT          19
#define HUB_CLASS_FEATURE_SELECTOR_C_PORT_RESET                 20

#define HUB_CLASS_FEATURE_SELECTOR_PORT_TEST                    21
#define HUB_CLASS_FEATURE_SELECTOR_PORT_INDICATOR               22


#define NON_REMOVABLE_DEVICE_ATTACHED      0x1
#define GANGED_POWER_SWICHING              (0<<0)
#define INDIVIDUAL_PORT_POWER_SWITHCING    (1<<0)
#define HUB_IS_PART_OF_COMPOUND_DEVICE     (1<<2)
#define HUB_NOT_PART_OF_COMPOUND_DEVICE    (0<<2)
#define GLOBAL_OVERCURRENT_PROTECT         (0<<3)
#define INDIVIDUAL_OVERCURRENT_PROTECT     (1<<3)
#define TT_THINK_TIME_08FS_BIT_TIMES        (0<<5)
#define TT_THINK_TIME_16FS_BIT_TIMES        (1<<5)
#define TT_THINK_TIME_24FS_BIT_TIMES        (2<<5)
#define TT_THINK_TIME_32FS_BIT_TIMES        (3<<5)
#define PORT_INDICATOR_NOT_SUPPORTED        (0<<7)
#define PORT_INDICATOR_SUPPORTED            (1<<7)

/* USB HUB Port Status, wPortStatus*/
#define HUB_PORT_STATUS_DEVICE_PRESENT          (1<<0)
#define HUB_PORT_STATUS_PORT_ENABLED            (1<<1)
#define HUB_PORT_STATUS_PORT_SUSPEND            (1<<2)
#define HUB_PORT_STATUS_PORT_OVERCURRENT        (1<<3)
#define HUB_PORT_STATUS_PORT_RESET_ASSERTED     (1<<4)
#define HUB_PORT_STATUS_PORT_POWER_OFF          (1<<8)
#define HUB_PORT_STATUS_PORT_LSDEV_ATTACHED     (1<<9)
#define HUB_PORT_STATUS_PORT_HSDEV_ATTACHED     (1<<10)
#define HUB_PORT_STATUS_PORT_TEST               (1<<11)
#define HUB_PORT_STATUS_PORT_INDICATOR          (1<<12)

/* USB HUB Port Status, wPortChange*/
#define HUB_PORT_CHANGE_CURRENT_CONNECT         (1<<16)
#define HUB_PORT_CHANGE_PORT_DISABLED           (1<<17)
#define HUB_PORT_CHANGE_PORT_RESUME_DONE        (1<<18)
#define HUB_PORT_CHANGE_PORT_OC_INDICATOR       (1<<19)
#define HUB_PORT_CHANGE_PORT_RESET_COMPLETE     (1<<20)

/*!
 * Device driver definitions
 */

/*!
 * USB device endpoint list
 */

typedef uint32_t endpointList_t[8];

/*
 * USB device setup packet
 */

typedef struct usbdSetupPacket {
    uint8_t bRequestType;	//! Characteristics of request 
    uint8_t bRequest;           //! Specific request
    uint16_t wValue;            //! Word-sized field that varies according to request
    uint16_t wIndex;            //! Index
    uint16_t wLength;           //! Number of bytes to transfer
}  __attribute__ ((packed)) usbdSetupPacket_t;            

/*!
 *  USB device endpoint queue head structure
 */

typedef struct usbdDeviceEndpointQueueHead {
    uint32_t endpointCharacteristics;	//! Endpoint Capabilities/Characteristics
    uint32_t currentDtd;		//! Current dTD Pointer
    uint32_t nextDtd;			//! Next dTD Pointer
    uint32_t dtdToken;			//! Token
    uint32_t dtdBuffer[5];		//! Buffer Pointers
    uint32_t reserved;
    usbdSetupPacket_t setupBuffer;	//! Set-up Buffer
    uint32_t reserved1[4];
} usbdDeviceEndpointQueueHead_t;

//! brief    USB endpoint pair sturcture
typedef struct usbdEndpointPair {
    usbdDeviceEndpointQueueHead_t out;
    usbdDeviceEndpointQueueHead_t in;
} usbdEndpointPair_t;

/*
 *  USB device endpoint transfer descriptor
 */
typedef struct usbdEndpointDtd {
    uint32_t nextDtd;		//! Next data transfer descriptor
    uint32_t dtdToken;		//! Token
    uint32_t dtdBuffer[5];	//! Buffers for data to be transferred
    uint32_t mallocPointer;     /* Used to keep track of the memory allocated for the data structure */
} usbdEndpointDtd_t;

/*!
 * Endpoint characteristics
 */
typedef enum usbdEndpointDirection {
    IN,
    OUT
} usbdEndpointDirection_t;

//! @brief    Structure to describle the endpoint
typedef struct usbdEndpointInfo {
    usbPortSpeed_t Speed;	//! Speed of this endpoint, High/Low/Full
    uint32_t endpointNumber;		//! Index of this endpoint
    usbdEndpointDirection_t endpointDirection;	//! Direction, IN/OUT
    uint32_t mult;		
    uint32_t maxPacketLength;	//! Max packet length supported by this endpoint
    bool interruptOnSetup;	//! Interupt issued when setup packet arrived
} usbdEndpointInfo_t;

/*!
 * Definitions for Setup packet
 */

/* Defines for commands in setup packets */
#define GET_DESCRIPTOR				0x8006
#define SET_CONFIGURATION			0x0009
#define SET_IDLE					0x210A
#define GET_HID_CLASS_DESCRIPTOR	0x8106
#define SET_FEATURE					0x0003

//! @name Board support functions
//!
//! The functions are called by the usb driver and must be defined by the board
//! support library or the application. Their purpose is to isolate the usb driver
//! from board-specific configuration.
//@{
void reset_usb_hub(void);
//@}

//! Host driver function prototypes
int usbh_init(usb_module_t *);
void usbh_bus_reset(usb_module_t *);
void get_setup_packet(usb_module_t *, uint32_t, uint32_t *, uint32_t *);
void usbh_enable_asynchronous_schedule(usb_module_t * port);
void usbh_disable_asynchronous_schedule(usb_module_t * port);
uint32_t usbh_periodic_schedule_init(usb_module_t *, uint32_t frame_list_size,
                                     uint32_t * frame_list);
usbhTransferDescriptor_t *usbh_qtd_init(uint32_t, uint32_t, uint32_t, uint32_t *);
usbhQueueHead_t *usbh_qh_init(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t swap32(uint32_t data);

//! device driver function prototypes
uint32_t usbd_device_init(usb_module_t * port, usbdEndpointPair_t * endpointList);
usbPortSpeed_t usbd_bus_reset(usb_module_t * port);
void usbd_get_setup_packet(usb_module_t * port, usbdEndpointPair_t * endpointList,
                           usbdSetupPacket_t * setupPacket);
void usbd_device_send_control_packet(usb_module_t * port, usbdEndpointPair_t * endpointList,
                                     uint8_t * buffer, uint32_t size);
void usbd_device_send_zero_len_packet(usb_module_t * port, usbdEndpointPair_t * endpointList,
                                      uint32_t endpoint);
void usbd_endpoint_qh_init(usbdEndpointPair_t * endpointList, usbdEndpointInfo_t * usbdEndpoint,
                           uint32_t nextDtd);
void usbd_add_dtd(usb_module_t * port, usbdEndpointPair_t * endpointList,
                  usbdEndpointInfo_t * usbdEndpoint, usbdEndpointDtd_t * new_dtd);
usbdEndpointDtd_t *usbd_dtd_init(uint32_t transferSize, uint32_t interruptOnComplete,
                                 uint32_t multOverride, uint32_t * bufferPointer);
usbdEndpointDtd_t *usbd_reclaim_dtd(usb_module_t * port, usbdEndpointPair_t * endpointList,
                                    usbdEndpointInfo_t * usbdEndpoint, usbdEndpointDtd_t * head);
void fillBuffer(uint32_t * buffer);

//! common prototypes

usbPortSpeed_t usb_get_port_speed(usb_module_t * port);
int usbEnableClocks(usb_module_t * port);
int usbEnableTransceiver(usb_module_t * port);
int get_menu_item(char *menu_table[]);

#define DTD_TERMINATE 0xDEAD001
#define QTD_TERMINATE 0xDEAD001
#define OUT_PID  0
#define IN_PID  1
#define SETUP_PID  2

#define EPS_FULL 0
#define EPS_LOW	1
#define EPS_HIGH 2

/*!
 * Memeory allocation configuration
 */
#define MAX_USB_BUFFER_SIZE 0x100
#define MAX_USB_DESC_SIZE 	0x40

#define MAX_QTD_TRANS_SIZE	0x5000
#define MAX_DTD_TRANS_SIZE	0x5000
#define MAX_QH_PACKET_SIZE	0x400

#endif /* _USB_H */
