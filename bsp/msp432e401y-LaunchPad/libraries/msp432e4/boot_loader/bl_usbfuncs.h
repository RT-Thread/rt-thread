//*****************************************************************************
//
// bl_usbfuncs.h - Prototypes for the subset of USB library functions used in
//                 the USB DFU boot loader.
//
// Copyright (c) 2008-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef __BL_USBFUNCS_H__
#define __BL_USBFUNCS_H__

//*****************************************************************************
//
//! \addtogroup bl_usb_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following macro allows compiler-independent syntax to be used to
// define packed structures.  A typical structure definition using these
// macros will look similar to the following example:
//
//   #ifdef __ICCARM__
//   #pragma pack(1)
//   #endif
//
//   typedef struct _PackedStructName
//   {
//      uint32_t ui32FirstField;
//      int8_t i8CharMember;
//      uint16_t ui16Short;
//   }
//   PACKED tPackedStructName;
//
//   #ifdef __ICCARM__
//   #pragma pack()
//   #endif
//
// The conditional blocks related to EWARM include the #pragma pack() lines
// only if the IAR Embedded Workbench compiler is being used.  Unfortunately,
// it is not possible to emit a #pragma from within a macro definition so this
// must be done explicitly.
//
//*****************************************************************************
#if defined(__TI_ARM__) ||      \
    defined(__CCARM__) ||       \
    defined(rvmdk) ||           \
    defined(__ARMCC_VERSION) || \
    defined(__GNUC__)
#define PACKED __attribute__ ((packed))
#elif defined(__ICCARM__)
#define PACKED
#else
#error Unrecognized COMPILER!
#endif

//*****************************************************************************
//
// Standard USB descriptor types.  These values are passed in the upper bytes
// of tUSBRequest.wValue on USBREQ_GET_DESCRIPTOR and also appear in the
// bDescriptorType field of standard USB descriptors.
//
//*****************************************************************************
#define USB_DTYPE_DEVICE        1
#define USB_DTYPE_CONFIGURATION 2
#define USB_DTYPE_STRING        3
#define USB_DTYPE_INTERFACE     4
#define USB_DTYPE_ENDPOINT      5
#define USB_DTYPE_DEVICE_QUAL   6
#define USB_DTYPE_OSPEED_CONF   7
#define USB_DTYPE_INTERFACE_PWR 8

#define USBShort(ui16Value)     (ui16Value & 0xff), (ui16Value >> 8)

#define USB_LANG_EN_US          0x0409      // English (United States)

#define USB_EP_DEV_IN           0x00002000  // Device IN endpoint

//*****************************************************************************
//
// All structures defined in this section of the header require byte packing of
// fields.  This is usually accomplished using the PACKED macro but, for IAR
// Embedded Workbench, this requires a pragma.
//
//*****************************************************************************
#ifdef __ICCARM__
#pragma pack(1)
#endif

//*****************************************************************************
//
// Definitions related to standard USB device requests (sections 9.3 & 9.4)
//
//*****************************************************************************

//*****************************************************************************
//
//! The standard USB request header as defined in section 9.3 of the USB 2.0
//! specification.
//
//*****************************************************************************
typedef struct
{
    //
    //! Determines the type and direction of the request.
    //
    uint8_t bmRequestType;

    //
    //! Identifies the specific request being made.
    //
    uint8_t bRequest;

    //
    //! Word-sized field that varies according to the request.
    //
    uint16_t wValue;

    //
    //! Word-sized field that varies according to the request; typically used
    //! to pass an index or offset.
    //
    uint16_t wIndex;

    //
    //! The number of bytes to transfer if there is a data stage to the
    //! request.
    //
    uint16_t wLength;
}
PACKED tUSBRequest;

//*****************************************************************************
//
// The following defines are used with the bmRequestType member of tUSBRequest.
//
// Request types have 3 bit fields:
// 4:0 - Is the recipient type.
// 6:5 - Is the request type.
// 7 - Is the direction of the request.
//
//*****************************************************************************
#define USB_RTYPE_DIR_IN        0x80
#define USB_RTYPE_DIR_OUT       0x00

#define USB_RTYPE_TYPE_M        0x60
#define USB_RTYPE_VENDOR        0x40
#define USB_RTYPE_CLASS         0x20
#define USB_RTYPE_STANDARD      0x00

#define USB_RTYPE_RECIPIENT_M   0x1f
#define USB_RTYPE_OTHER         0x03
#define USB_RTYPE_ENDPOINT      0x02
#define USB_RTYPE_INTERFACE     0x01
#define USB_RTYPE_DEVICE        0x00

//*****************************************************************************
//
// Standard USB requests IDs used in the bRequest field of tUSBRequest.
//
//*****************************************************************************
#define USBREQ_GET_STATUS       0x00
#define USBREQ_CLEAR_FEATURE    0x01
#define USBREQ_SET_FEATURE      0x03
#define USBREQ_SET_ADDRESS      0x05
#define USBREQ_GET_DESCRIPTOR   0x06
#define USBREQ_SET_DESCRIPTOR   0x07
#define USBREQ_GET_CONFIG       0x08
#define USBREQ_SET_CONFIG       0x09
#define USBREQ_GET_INTERFACE    0x0a
#define USBREQ_SET_INTERFACE    0x0b
#define USBREQ_SYNC_FRAME       0x0c

//*****************************************************************************
//
// Data returned from a USBREQ_GET_STATUS request to a device.
//
//*****************************************************************************
#define USB_STATUS_SELF_PWR     0x0001  // Currently self powered.
#define USB_STATUS_BUS_PWR      0x0000  // Currently bus-powered.
#define USB_STATUS_PWR_M        0x0001  // Mask for power mode.
#define USB_STATUS_REMOTE_WAKE  0x0002  // Remote wake-up is currently enabled.


//*****************************************************************************
//
//! This structure describes the USB configuration descriptor as defined in
//! USB 2.0 specification section 9.6.3.  This structure also applies to the
//! USB other speed configuration descriptor defined in section 9.6.4.
//
//*****************************************************************************
typedef struct
{
    //
    //! The length of this descriptor in bytes.  All configuration descriptors
    //! are 9 bytes long.
    //
    uint8_t bLength;

    //
    //! The type of the descriptor.  For a configuration descriptor, this will
    //! be USB_DTYPE_CONFIGURATION (2).
    //
    uint8_t bDescriptorType;

    //
    //! The total length of data returned for this configuration.  This
    //! includes the combined length of all descriptors (configuration,
    //! interface, endpoint and class- or vendor-specific) returned for this
    //! configuration.
    //
    uint16_t wTotalLength;

    //
    //! The number of interface supported by this configuration.
    //
    uint8_t bNumInterfaces;

    //
    //! The value used as an argument to the SetConfiguration standard request
    //! to select this configuration.
    //
    uint8_t bConfigurationValue;

    //
    //! The index of a string descriptor describing this configuration.
    //
    uint8_t iConfiguration;

    //
    //! Attributes of this configuration.
    //
    uint8_t bmAttributes;

    //
    //! The maximum power consumption of the USB device from the bus in this
    //! configuration when the device is fully operational.  This is expressed
    //! in units of 2mA so, for example, 100 represents 200mA.
    //
    uint8_t bMaxPower;
}
PACKED tConfigDescriptor;

//*****************************************************************************
//
// Flags used in constructing the value assigned to the field
// tConfigDescriptor.bmAttributes.  Note that bit 7 is reserved and must be set
// to 1.
//
//*****************************************************************************
#define USB_CONF_ATTR_PWR_M     0xC0

#define USB_CONF_ATTR_SELF_PWR  0xC0
#define USB_CONF_ATTR_BUS_PWR   0x80
#define USB_CONF_ATTR_RWAKE     0xA0

//*****************************************************************************
//
// Feature Selectors (tUSBRequest.wValue) passed on USBREQ_CLEAR_FEATURE and
// USBREQ_SET_FEATURE.
//
//*****************************************************************************
#define USB_FEATURE_EP_HALT     0x0000  // Endpoint halt feature.
#define USB_FEATURE_REMOTE_WAKE 0x0001  // Remote wake feature, device only.
#define USB_FEATURE_TEST_MODE   0x0002  // Test mode

//*****************************************************************************
//
//! This structure describes the USB string descriptor for index 0 as defined
//! in USB 2.0 specification section 9.6.7.  Note that the number of language
//! IDs is variable and can be determined by examining bLength.  The number of
//! language IDs present in the descriptor is given by ((bLength - 2) / 2).
//
//*****************************************************************************
typedef struct
{
    //
    //! The length of this descriptor in bytes.  This value will vary
    //! depending upon the number of language codes provided in the descriptor.
    //
    uint8_t bLength;

    //
    //! The type of the descriptor.  For a string descriptor, this will be
    //! USB_DTYPE_STRING (3).
    //
    uint8_t bDescriptorType;

    //
    //! The language code (LANGID) for the first supported language.  Note that
    //! this descriptor may support multiple languages, in which case, the
    //! number of elements in the wLANGID array will increase and bLength will
    //! be updated accordingly.
    //
    uint16_t wLANGID[1];
}
PACKED tString0Descriptor;

//*****************************************************************************
//
//! This structure describes the USB string descriptor for all string indexes
//! other than 0 as defined in USB 2.0 specification section 9.6.7.
//
//*****************************************************************************
typedef struct
{
    //
    //! The length of this descriptor in bytes.  This value will be 2 greater
    //! than the number of bytes comprising the UNICODE string that the
    //! descriptor contains.
    //
    uint8_t bLength;

    //
    //! The type of the descriptor.  For a string descriptor, this will be
    //! USB_DTYPE_STRING (3).
    //
    uint8_t bDescriptorType;

    //
    //! The first byte of the UNICODE string.  This string is not NULL
    //! terminated.  Its length (in bytes) can be computed by subtracting 2
    //! from the value in the bLength field.
    //
    uint8_t bString;
}
PACKED tStringDescriptor;

//*****************************************************************************
//
// Return to default packing when using the IAR Embedded Workbench compiler.
//
//*****************************************************************************
#ifdef __ICCARM__
#pragma pack()
#endif

//*****************************************************************************
//
// Some standard USB class definitions.
//
//*****************************************************************************
#define USB_CLASS_APP_SPECIFIC  0xfe
#define USB_CLASS_VEND_SPECIFIC 0xff

//*****************************************************************************
//
// The following are values that are returned from USBEndpointStatus().  The
// USB_HOST_* values are used when the USB controller is in host mode and the
// USB_DEV_* values are used when the USB controller is in device mode.
//
//*****************************************************************************
#define USB_DEV_RX_SENT_STALL   0x00400000  // Stall was sent on this endpoint
#define USB_DEV_RX_DATA_ERROR   0x00080000  // CRC error on the data
#define USB_DEV_RX_OVERRUN      0x00040000  // OUT packet was not loaded due to
                                            // a full FIFO
#define USB_DEV_RX_FIFO_FULL    0x00020000  // RX FIFO full
#define USB_DEV_RX_PKT_RDY      0x00010000  // Data packet ready
#define USB_DEV_TX_NOT_COMP     0x00000080  // Large packet split up, more data
                                            // to come
#define USB_DEV_TX_SENT_STALL   0x00000020  // Stall was sent on this endpoint
#define USB_DEV_TX_UNDERRUN     0x00000004  // IN received with no data ready
#define USB_DEV_TX_FIFO_NE      0x00000002  // The TX FIFO is not empty
#define USB_DEV_TX_TXPKTRDY     0x00000001  // Transmit still being transmitted
#define USB_DEV_EP0_SETUP_END   0x00000010  // Control transaction ended before
                                            // Data End seen
#define USB_DEV_EP0_SENT_STALL  0x00000004  // Stall was sent on this endpoint
#define USB_DEV_EP0_IN_PKTPEND  0x00000002  // Transmit data packet pending
#define USB_DEV_EP0_OUT_PKTRDY  0x00000001  // Receive data packet ready

//*****************************************************************************
//
// This value specifies the maximum size of transfers on endpoint 0 as 64
// bytes.  This value is fixed in hardware as the FIFO size for endpoint 0.
//
//*****************************************************************************
#define MAX_PACKET_SIZE_EP0     64

//*****************************************************************************
//
// These values are used to indicate which endpoint to access.
//
//*****************************************************************************
#define USB_EP_0                0x00000000  // Endpoint 0

//*****************************************************************************
//
// These macros allow conversion between 0-based endpoint indices and the
// USB_EP_x values required when calling various USB APIs.
//
//*****************************************************************************
#define INDEX_TO_USB_EP(x)      ((x) << 4)
#define USB_EP_TO_INDEX(x)      ((x) >> 4)

//*****************************************************************************
//
// The following are values that can be passed to USBEndpointDataSend() as the
// ui32TransType parameter.
//
//*****************************************************************************
#define USB_TRANS_OUT           0x00000102  // Normal OUT transaction
#define USB_TRANS_IN            0x00000102  // Normal IN transaction
#define USB_TRANS_IN_LAST       0x0000010a  // Final IN transaction (for
                                            // endpoint 0 in device mode)
#define USB_TRANS_SETUP         0x0000110a  // Setup transaction (for endpoint
                                            // 0)
#define USB_TRANS_STATUS        0x00000142  // Status transaction (for endpoint
                                            // 0)

//*****************************************************************************
//
// Function prototype for any standard USB request.
//
//*****************************************************************************
typedef void (* tStdRequest)(tUSBRequest *psUSBRequest);

//*****************************************************************************
//
// Data structures defined in bl_usb.c but referenced elsewhere.
//
//*****************************************************************************
extern const uint8_t g_pui8DFUConfigDescriptor[];
extern const uint8_t g_pui8DFUDeviceDescriptor[];
extern const uint8_t * const g_ppui8StringDescriptors[];

#define NUM_STRING_DESCRIPTORS  4

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Prototypes of the various USB handler functions.
//
//*****************************************************************************
extern void HandleRequests(tUSBRequest *psUSBRequest);
extern void HandleConfigChange(uint32_t ui32Info);
extern void HandleEP0Data(uint32_t ui32Info);
extern void HandleReset(void);
extern void HandleDisconnect(void);
extern void HandleSetAddress(void);

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void USBDevEndpoint0DataAck(bool bIsLastPacket);
extern int32_t USBEndpoint0DataGet(uint8_t *pui8Data, uint32_t *pui32Size);
extern int32_t USBEndpoint0DataPut(uint8_t *pui8Data, uint32_t ui32Size);
extern int32_t USBEndpoint0DataSend(uint32_t ui32TransType);
extern void USBBLInit(void);
extern void USBBLStallEP0(void);
extern void USBBLRequestDataEP0(uint8_t *pui8Data, uint32_t ui32Size);
extern void USBBLSendDataEP0(uint8_t *pui8Data, uint32_t ui32Size);
extern void USBDeviceEnumHandler(void);
extern void USBDeviceEnumResetHandler(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __BL_USBFUNCS_H__
