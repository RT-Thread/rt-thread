/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file usb_descriptor.c
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains USB descriptors for Audio Application
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "derivative.h"
#include "types.h"
#include "usb_class.h"
#include "usb_descriptor.h"

#ifndef __NO_SETJMP
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

#if ((defined __MCF52xxx_H__) || (defined __MK_xxx_H__))
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST	const
#endif



/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/* structure containing details of all the endpoints used by this device */
USB_DESC_CONST USB_ENDPOINTS usb_desc_ep = { 
    AUDIO_DESC_ENDPOINT_COUNT, // 2
    {
        // for data endpoint
        {
            AUDIO_ENDPOINT,				// 1
            USB_ISOCHRONOUS_PIPE,		// iso
            USB_RECV,					// OUT
            AUDIO_ENDPOINT_PACKET_SIZE,	// 8
        },
        // for feedback endpoint
        {
            AUDIO_FEEDBACK_ENDPOINT,			// 2
            USB_ISOCHRONOUS_PIPE,				// iso
            USB_SEND,							// IN
            AUDIO_FEEDBACK_ENDPOINT_PACKET_SIZE	// 3
        }
    }
};

/* *********************************************************************
 * Structure containing Entities(terminals, units, clocks) from the AC interface
 ************************************************************************ */                                
USB_DESC_CONST USB_AUDIO_UNITS usb_audio_unit = 
{
    AUDIO_UNIT_COUNT,
#if AUDIO_CLASS_2_0
    {
        {0x10,AUDIO_CONTROL_CLOCK_SOURCE},
        {0x20,AUDIO_CONTROL_INPUT_TERMINAL}, 
        {0x30,AUDIO_CONTROL_FEATURE_UNIT},
        {0x40,AUDIO_CONTROL_OUTPUT_TERMINAL},
    }
#else
    {
        {0x01,AUDIO_CONTROL_INPUT_TERMINAL}, 
        {0x02,AUDIO_CONTROL_FEATURE_UNIT},
        {0x03,AUDIO_CONTROL_OUTPUT_TERMINAL},
    }
#endif /* AUDIO_CLASS_2_0 */
};

uint_8 USB_DESC_CONST g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    DEVICE_DESCRIPTOR_SIZE,               /* "Device Descriptor Size        */
    USB_DEVICE_DESCRIPTOR,                /* "Device" Type of descriptor    */
    0x00,0x02,                            /*  BCD USB version               */
    0xEF,                                 /*  Device Class is indicated in
                                             the interface descriptors     */
    0x02,                                 /*  Device Subclass is indicated
                                             in the interface descriptors  */
    0x01,                                 /*  Device Protocol               */
    CONTROL_MAX_PACKET_SIZE,              /*  Max Packet size               */
    0xA2,0x15,                            /*  Vendor ID  */
    0x01, 0x02,                           /*  Product ID */
    0x00, 0x02,                           /*  BCD Device version */
    0x01,                                 /*  Manufacturer string index     */
    0x02,                                 /*  Product string index          */
    0x00,                                 /*  Serial number string index    */
    0x01                                  /*  Number of configurations      */
};

uint_8 USB_DESC_CONST g_device_qualifier_descriptor[DEVICE_QUALIFIER_DESCRIPTOR_SIZE] =
{
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,   /* bLength(10) */
    USB_DEVQUAL_DESCRIPTOR,             /* bDescriptorType(device qualifier) */
    0x00,0x02,                          /* bcdUSB(V2.00) */
    0xEF,                               /* bDeviceClass */
    0x02,                               /* bDeviceSubClass 
                                            Device Subclass is indicated
                                            in the interface descriptors  */
    0x01,                               /* bDeviceProtocol */
    CONTROL_MAX_PACKET_SIZE,            /* bMaxPacketSize0 */
    0x00,                               /* bNumConfigurations */
    0x00                                /* bReserved */
};


/*****************************************************************************/
uint_8 USB_DESC_CONST g_config_descriptor[CONFIG_DESC_SIZE] = 
{
#if AUDIO_CLASS_2_0
    /* Standard Configuration Descriptor */
    CONFIG_ONLY_DESC_SIZE,  /* bLength(0x09) */
    0x02,                   /* bDescriptorType(0x02) */
    CONFIG_DESC_SIZE, 0x00, /* wTotalLength(174) */
    0x02,                   /* bNumInterfaces(0x02):
                                INTERFACE 0: AudioControl
                                INTERFACE 1: AudioStreaming */
    0x01,                   /* bConfigurationValue(0x01) */
    0x00,                   /* iConfiguration(0x00) */
    (BUS_POWERED | SELF_POWERED), /* bmAttributes(0xC0) */
    0xFA,                   /* bMaxPower(0xFA): 500mA */

    /* Standard Interface Association Descriptor */
    0x08,                                   /* bLength(0x08) */
    USB_INTERFACE_ASSOCIATION_DESCRIPTOR,   /* bDescriptorType(0x0B) */
    0x00,                                   /* bFirstInterface(0x00) */
    0x02,                                   /* bInterfaceCount(0x02) */
    0x01,                                   /* bFunctionClass(0x01): AUDIO */
    0x00,                                   /* bFunctionSubClass(0x00) */
    0x20,                                   /* bFunctionProtocol(0x2000): 2.0 AF_VERSION_02_00 */
    0x00,                                   /* iFunction(0x00) */

    /******************** INTERFACE 0 ************************/
    /* AUDIO CONTROL Interface */
    /* Standard AC Interface Descriptor(4.7.1) */
    0x09,       /* bLength(0x09) */
    0x04,       /* bDescriptorType(0x04): INTERFACE */
    0x00,       /* bInterfaceNumber(0x00) */
    0x00,       /* bAlternateSetting(0x00) */
    0x00,       /* bNumEndpoints(0x00) */
    0x01,       /* bInterfaceClass(0x01): AUDIO */
    0x01,       /* bInterfaceSubClass(0x01): AUDIOCONTROL */
    0x20,       /* bInterfaceProtocol(0x20): IP 2.0 IP_VERSION_02_00 */
    0x07,       /* iInterface(0x07): Not Requested */

    /* Class-Specific AC Interface Header Descriptor(4.7.2) */
    0x09,       /* bLength(0x09) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x01,       /* bDescriptorSubType(0x01): HEADER */
    0x00, 0x02, /* bcdADC(0x0200): 2.0 */
    0x01,       /* bCategory(0x01): DESKTOP_SPEAKER */
    //0x40, 0x00, /* wTotalLength(64): 9 + 8 + 17 + 18 + 12 (2 channels)
    0x3C, 0x00, /* wTotalLength(60): 9 + 8 + 17 + 14 + 12 (1 channel)
                        Audio Control Interface size */
    0x00,       /* bmControls(0b00000000) */

    /* Clock Source Descriptor(4.7.2.1) */
    0x08,       /* bLength(0x08) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x0A,       /* bDescriptorSubType(0x0A): CLOCK_SOURCE */
    0x10,       /* bClockID(0x10): CLOCK_SOURCE_ID */
    0x01,       /* bmAttributes(0x01): internal fixed clock */
    0x07,       /* bmControls(0x07):
                        clock frequency control: 0b11 - host programmable; 
                        clock validity control: 0b01 - host read only */
    0x00,       /* bAssocTerminal(0x00) */
    0x01,       /* iClockSource(0x01): Not requested */

    /* Input Terminal Descriptor(4.7.2.4) */
    0x11,       /* bLength(0x11): 17 */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,       /* bDescriptorSubType(0x02): INPUT_TERMINAL */
    0x20,       /* bTerminalID(0x20): INPUT_TERMINAL_ID */
    0x01, 0x01, /* wTerminalType(0x0101): USB streaming */
    0x00,       /* bAssocTerminal(0x00) */
    0x10,       /* bCSourceID(0x10): CLOCK_SOURCE_ID */
    NB_CHANNELS,/* bNrChannels(0x01) */
    0x00, 0x00, 0x00, 0x00, /* bmChannelConfig(0x00): Mono, no spatial location */
    0x00,       /* iChannelNames */
    0x00, 0x00, /* bmControls(0x0000) */
    0x02,       /* iTerminal(0x02): not requested */

    /* Feature Unit Descriptor(4.7.2.8) */
    //0x12,       /* bLength(0x12): 6 + (ch + 1) * 4, 2 channels */
    0x0E,       /* bLength(0x0E): 6 + (ch + 1) * 4, 1 channel */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x06,       /* bDescriptorSubType(0x06): FEATURE_UNIT */
    0x30,       /* bUnitID(0x30): FEATURE_UNIT_ID */
    0x20,       /* bSourceID(0x20): INPUT_TERMINAL_ID */
    0x0F, 0x00, 0x00, 0x00, /* bmaControls(0)(0x0000000F): Master Channel 0
                                    0b11: Mute read/write 
                                    0b11: Volume read/write */
    0x00, 0x00, 0x00, 0x00, /* bmaControls(1)(0x00000000): Logical Channel 1
     */
    0x00,       /* iFeature(0x00) */

    /* Output Terminal Descriptor(4.7.2.5) */
    0x0C,       /* bLength(12) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x03,       /* bDescriptorSubType(0x03): OUTPUT_TERMINAL */
    0x40,       /* bTerminalID(0x40) */
    0x01, 0x01, /* wTerminalType(0x0101): USB_STREAMING */
    0x00,       /* bAssocTerminal(0x00): no association */
    0x30,       /* bSourceID(0x30): FEATURE_UNIT_ID */
    0x10,       /* bCSourceID(0x10): CLOCK_SOURCE_ID */
    0x00, 0x00, /* bmControls(0x0000) */
    0x00,       /* iTerminal(0x00): Not Requested */
    /******************** INTERFACE 0 ************************/

    /******************** INTERFACE 1 ************************/
    /* AUDIO STREAMING Interface */
    /* Standard AS Interface Descriptor(4.9.1) */
    /* Interface 1, Alternate 0 */
    /* default alternate setting with 0 bandwidth */
    0x09,       /* bLength(9) */
    0x04,       /* bDescriptorType(0x04): INTERFACE */
    0x01,       /* bInterfaceNumber(0x01) */
    0x00,       /* bAlternateSetting(0x00) */
    0x00,       /* bNumEndpoints(0x00) */
    0x01,       /* bInterfaceClass(0x01): AUDIO */
    0x02,       /* bInterfaceSubClass(0x02): AUDIOSTREAMING */
    0x20,       /* bInterfaceProtocol(0x20): IP 2.0 */
    0x08,       /* iInterface */

    /* Standard AS Interface Descriptor(4.9.1) */
    /* INterface 1, Alternate 1 */
    /* alternate interface for data streaming */
    0x09,       /* bLength(9) */
    0x04,       /* bDescriptorType(0x04): INTERFACE */
    0x01,       /* bInterfaceNumber(0x01) */
    0x01,       /* bAlternateSetting(0x01) */
    0x02,       /* bNumEndpoints(0x02) */
    0x01,       /* bInterfaceClass(0x01): AUDIO */
    0x02,       /* bInterfaceSubClass(0x02): AUDIO_STREAMING */
    0x20,       /* bInterfaceProtocol(0x20): IP 2.0 */
    0x09,       /* iInterface */

    /* Class-Specific AS Interface Descriptor(4.9.2) */
    0x10,       /* bLength(16) */
    0x24,       /* bDescriptorType(0x024): CS_INTERFACE */
    0x01,       /* bDescriptorSubType(0x01): AS_GENERAL */
    0x20,       /* bTerminalLink(0x20): INPUT_TERMINAL_ID */
    0x00,       /* bmControls(0x00) */
    0x01,       /* bFormatType(0x01): FORMAT_TYPE_I */
    0x01, 0x00, 0x00, 0x00, /* bmFormats(0x00000001): PCM */
    0x02,       /* bNrChannels(0x02): NB_CHANNELS */
    0x03, 0x00, 0x00, 0x00, /* bmChannelCOnfig(0x00000003) */
    0x00,       /* iChannelNames(0x00): None */

    /* Type I Format Type Descriptor(2.3.1.6 - Audio Formats) */
    0x06,       /* bLength(6) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,       /* bDescriptorSubtype(0x02): FORMAT_TYPE */
    0x01,       /* bFormatType(0x01): FORMAT_TYPE_I */
    0x04,       /* bSubSlotSize(0x01) */
    0x18,       /* bBitResolution(0x18): 8 bits per sample */

    /* Standard AS Isochronous Audio Data Endpoint Descriptor(4.10.1.1) */
    0x07,       /* bLength(7) */
    0x05,       /* bDescriptorType(0x05): ENDPOINT_DESCRIPTOR */
    EP01_OUT,   /* bEndpointAddress(0x01) */
    0x05,       /* bmAttributes(0x02): iso+asynch+data */
    //0x88, 0x01, /* wMaxPacketSize(0x0188): 392(49 samples * 4 bytes * 2 channels) */
    0x08, 0x00, /* wMaxPacketSize(0x0008): 8(8 samples * 1 bytes * 1 channel) */
#if HIGH_SPEED_DEVICE
    0x04,       /* bInterval(0x04): 2^x ms */
#else
    0x01,       /* bInterval(0x01): 2^x ms */
#endif

    /* Class-Specific AS IsochronousAudio Data Endpoint Descriptor(4.10.1.2) */
    0x08,       /* bLength(8) */
    0x25,       /* bDescriptorType(0x25): CS_ENDPOINT */
    0x01,       /* bDescriptorSubtype(0x01): EP_GENERAL */
    0x00,       /* bmAttributes(0x00): MaxPacketsOnly = FALSE */
    0x00,       /* bmControls(0x00) */
    0x00,       /* bLockDelayUnits(0x00) */
    0x00, 0x00, /* wLockDelay(0x0000) */

    /* Standard AS Isochronous Audio Data Endpoint Descriptor(4.10.1.1) */
    0x07,       /* bLength(7) */
    0x05,       /* bDescriptorType(0x05): ENDPOINT_DESCRIPTOR */
    EP02_IN,    /* bEndpointAddress(0x82) */
    0x11,       /* bmAttributes(0x11): iso+feedback */
    0x04, 0x00, /* wMaxPacketSize(0x0004) */
#if HIGH_SPEED_DEVICE
    0x04,       /* bInterval(0x04): 2^x ms */
#else
    0x01,       /* bInterval(0x01): 2^x ms */
#endif
    /******************** INTERFACE 1 ************************/


#else
    CONFIG_ONLY_DESC_SIZE,     /*  Configuration Descriptor Size - always 9 bytes*/
    USB_CONFIG_DESCRIPTOR,     /* "Configuration" type of descriptor */
    CONFIG_DESC_SIZE, 0x00,    /*  Total length of the Configuration descriptor */
    0x02,                      /*  NumInterfaces */
    0x01,                      /*  Configuration Value */
    0,                         /*  Configuration Description String Index*/
    (BUS_POWERED | SELF_POWERED),
    /* S08/CFv1 are both self powered (its compulsory to set bus powered)*/
    /* Attributes.support RemoteWakeup and self power */
    0x32,                   /*  Current draw from bus */

    /* AUDIO CONTROL INTERFACE DESCRIPTOR */
    IFACE_ONLY_DESC_SIZE,      /* Size of this descriptor */
    USB_IFACE_DESCRIPTOR,      /* INTERFACE descriptor */
    0x00,                      /* Index of this interface */
    0x00,                      /* Index of this setting */
    0x00,                      /* 0 endpoint */
    USB_DEVICE_CLASS_AUDIO,    /* AUDIO */
    USB_SUBCLASS_AUDIOCONTROL, /* AUDIO_CONTROL */
    0x00,                      /* Unused */
    0x00,                      /* Unused */

    /* Interface Header Audio Class Descriptor */
    /* Audio class-specific interface header */
    HEADER_ONLY_DESC_SIZE,           /* bLength (9) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType (CS_INTERFACE) */
    AUDIO_CONTROL_HEADER,            /* bDescriptorSubtype (HEADER) */
    0x00,0x01,                       /* bcdADC (1.0) */
    0x2B,0x00,                       /* wTotalLength (43) */
    0x01,                            /* bInCollection (1 streaming interface) */
    0x01,                            /* baInterfaceNr (interface 1 is stream) */

    /* Input Terminal Audio Class Descriptor */
    /* Audio class-specific input terminal */
    INPUT_TERMINAL_ONLY_DESC_SIZE,   /* bLength (12) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType (CS_INTERFACE) */
    AUDIO_CONTROL_INPUT_TERMINAL,    /* bDescriptorSubtype (INPUT_TERMINAL) */
    0x01,                            /* bTerminalID (1) */
    0x01,0x01,                       /* wTerminalType (radio receiver) */
    0x00,                            /* bAssocTerminal (none) */
    NB_CHANNELS,                     /* bNrChannels (2) */
    0x00,0x00,                       /* wChannelConfig (left, right) */
    0x00,                            /* iChannelNames (none) */
    0x00,                            /* iTerminal (none) */

    /* Feature Unit Audio Class Descriptor */
    /* Audio class-specific feature unit */    
    FEATURE_UNIT_ONLY_DESC_SIZE,     /* bLength (9) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType (CS_INTERFACE) */
    AUDIO_CONTROL_FEATURE_UNIT,      /* bDescriptorSubtype (FEATURE_UNIT) */
    0x02,                            /* bUnitID (2) */
    0x01,                            /* bSourceID (input terminal 1) */
    0x01,                            /* bControlSize (1 bytes) */
    (
        AUDIO_AUTOMATIC_GAIN_CONTROL |  /* Master controls */
        AUDIO_TREBLE_CONTROL         |  /* Controls enabled: AGC, TREBLE, BASS, VOLUME, MUTE */
        AUDIO_BASS_CONTROL           |
        AUDIO_VOLUME_CONTROL         |
        AUDIO_MUTE_CONTROL
    ),
    0x00,                            /* Channel 0 controls */
    0x00,                            /* iFeature */

    /* Output Terminal Audio Class Descriptor */
    /* Audio class-specific output terminal */ 
    OUTPUT_TERMINAL_ONLY_DESC_SIZE,  /* bLength (9) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType (CS_INTERFACE) */
    AUDIO_CONTROL_OUTPUT_TERMINAL,   /* bDescriptorSubtype (OUTPUT_TERMINAL) */
    0x03,                            /* bTerminalID (3) */
    0x01,0x03,                       /* wTerminalType (USB streaming) */
    0x00,                            /* bAssocTerminal (none) */
    0x02,                            /* bSourceID (feature unit 2) */
    0x00,                            /* iTerminal (none) */ 

    /* Audio Stream Interface Descriptor(Interface 1, Alternate Setting 0) */
    /* USB speaker standard AS interface descriptor - audio streaming operational 
    (Interface 1, Alternate Setting 0) */
    IFACE_ONLY_DESC_SIZE,            /* bLength (9) */
    USB_IFACE_DESCRIPTOR,            /* bDescriptorType (CS_INTERFACE) */
    0x01,                            /* interface Number: 1 */
    0x00,                            /* Alternate Setting: 0 */
    0x00,                            /* not used (Zero Bandwidth) */
    USB_DEVICE_CLASS_AUDIO,          /* USB DEVICE CLASS AUDIO */
    USB_SUBCLASS_AUDIOSTREAM,        /* AUDIO SUBCLASS AUDIOSTREAMING */
    0x00,                            /* AUDIO PROTOCOL UNDEFINED */
    0x00,                            /* Unused */

    /* Alternate Audio Interface Descriptor(Interface 1, Alternate Setting 1) */
    /* USB speaker standard AS interface descriptor - audio streaming operational 
    (Interface 1, Alternate Setting 1) */
    IFACE_ONLY_DESC_SIZE,            /* bLength (9) */
    USB_IFACE_DESCRIPTOR,            /* bDescriptorType (CS_INTERFACE) */
    0x01,                            /* interface Number: 1 */
    0x01,                            /* Alternate Setting: 1 */
    0x02,                            /* TWO Endpoints DATA and Feedback endpoints */
    USB_DEVICE_CLASS_AUDIO,          /* USB DEVICE CLASS AUDIO */
    USB_SUBCLASS_AUDIOSTREAM,        /* AUDIO SUBCLASS AUDIOSTREAMING */
    0x00,                            /* AUDIO PROTOCOL UNDEFINED */
    0x00,                            /* Unused */

    /* Audio Stream Audio Class Descriptor */
    /* USB speaker standard General AS interface descriptor */
    AUDIO_STREAMING_IFACE_DESC_SIZE, /* bLength (7) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType (CS_INTERFACE) */
    AUDIO_STREAMING_GENERAL,         /* GENERAL subtype  */
    0x01,                            /* Unit ID of output terminal */
    INTERFACE_DELAY,                 /* Interface delay */
    PCM_FORMAT,0x00,                 /* PCM format */

    /* Format Type Audio Descriptor */
    /* USB speaker audio type I format interface descriptor */
    AUDIO_INTERFACE_DESC_TYPE_I_SIZE, 	/* bLength (11) */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, 	/* bDescriptorType (CS_INTERFACE) */
    AUDIO_STREAMING_FORMAT_TYPE,     	/* DescriptorSubtype: AUDIO STREAMING FORMAT TYPE */
    AUDIO_FORMAT_TYPE_I,             	/* Format Type: Type I */
    NB_CHANNELS,                       	/* Number of Channels: one channel */
    SUB_FRAME_SIZE,                            	/* SubFrame Size: one byte per audio subframe */
    BIT_RESOLUTION,                            	/* Bit Resolution: 8 bits per sample */
    0x01,                            	/* One frequency supported */
    0x40,0x1F,0x00,                  	/* 8 kHz */
    //0x80,0xBB,0x00,					/* 48 kHz */

    /* Isochronous Endpoint Descriptor */
    AUDIO_STREAMING_ENDP_DESC_SIZE, // bLength
    USB_AUDIO_DESCRIPTOR,		    // bDescriptorType
    AUDIO_ENDPOINT_GENERAL,		    // bDescriptorSubType
    0x80,		                    // bmAttributes
    0x00,		                    // bLockDelayUnits
    0x00,0x00,	                    // wLockDelay

    /* EP1. Isochronous Endpoint Audio Class Descriptor */
    ENDP_ONLY_DESC_SIZE,        // bLength
    USB_ENDPOINT_DESCRIPTOR,    // endpoint descriptor type
    EP01_OUT,                   // host->dev, ep 1
    0x05,                       // iso + async + data
    0x08,0x00,                  /* wMaxPacketSize(8) */
    //0xC4,0x00,                /* wMaxPacketSize(196) */
#if HIGH_SPEED_DEVICE
    0x04,                       // interval polling(2^x ms)
#else
    0x01,                       // interval polling(2^x ms)
#endif
    0x00,                       // bRefresh
    EP02_IN,                    // bSyncAddress

    // EP2. EP descriptor (standard) - feedback endpoint
    ENDP_ONLY_DESC_SIZE,        // bLength
    USB_ENDPOINT_DESCRIPTOR,    // bDescriptorType
    EP02_IN,                    // dev->host, ep 2
    0x15,                       // iso + asynch + feedback
    0x03,0x00,                  // wMaxPacketSize
#if HIGH_SPEED_DEVICE
    0x04,                       // interval polling(2^x ms)
#else
    0x01,                       // interval polling(2^x ms)
#endif
    0x05,                       // bRefresh(32ms)
    0x00,                       // bSyncAddress
#endif /* AUDIO_CLASS_2_0 */
};


uint_8 USB_DESC_CONST USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_0),
    USB_STRING_DESCRIPTOR,
    0x09,
    0x04 /* equiavlent to 0x0409 */
};

uint_8 USB_DESC_CONST USB_STR_1[USB_STR_1_SIZE+USB_STR_DESC_SIZE] =
{  
    sizeof(USB_STR_1),
    USB_STRING_DESCRIPTOR,
    'F',0,
    'R',0,
    'E',0,
    'E',0,
    'S',0,
    'C',0,
    'A',0,
    'L',0,
    'E',0,
    ' ',0,
    'S',0,
    'E',0,
    'M',0,
    'I',0,
    'C',0,
    'O',0,
    'N',0,
    'D',0,
    'U',0,
    'C',0,
    'T',0,
    'O',0,
    'R',0,
    ' ',0,
    'I',0,
    'N',0,
    'C',0,
    '.',0
};

uint_8 USB_DESC_CONST USB_STR_2[USB_STR_2_SIZE+USB_STR_DESC_SIZE] =
{
    sizeof(USB_STR_2),
    USB_STRING_DESCRIPTOR,
    'U',0,
    'S',0,
    'B',0,
    ' ',0,
    'A',0,
    'U',0,
    'D',0,
    'I',0,
    'O',0,
    ' ',0,
    'D',0,
    'E',0,
    'M',0,
    'O',0,
};

uint_8 USB_DESC_CONST USB_STR_n[USB_STR_n_SIZE+USB_STR_DESC_SIZE] =
{  
    sizeof(USB_STR_n),
    USB_STRING_DESCRIPTOR,
    'B',0,
    'A',0,
    'D',0,
    ' ',0,
    'S',0,
    'T',0,
    'R',0,
    'I',0,
    'N',0,
    'G',0,
    ' ',0,
    'I',0,
    'N',0,
    'D',0,
    'E',0,
    'X',0
};


USB_PACKET_SIZE const g_std_desc_size[USB_MAX_STD_DESCRIPTORS+1] =
{
    0,
    DEVICE_DESCRIPTOR_SIZE,
    CONFIG_DESC_SIZE,
    0, /* string */
    0, /* Interface */
    0, /* Endpoint */
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    0, /* other speed config */
    0
};

uint_8_ptr const g_std_descriptors[USB_MAX_STD_DESCRIPTORS+1] =
{
    NULL,
    (uint_8_ptr)g_device_descriptor,
    (uint_8_ptr)g_config_descriptor,
    NULL, /* string */
    NULL, /* Interface */
    NULL, /* Endpoint */
    (uint_8_ptr)g_device_qualifier_descriptor,
    NULL, /* other speed config*/
    NULL
};

uint_8 const g_string_desc_size[USB_MAX_STRING_DESCRIPTORS] =
{
    sizeof(USB_STR_0),
    sizeof(USB_STR_1),
    sizeof(USB_STR_2),
    sizeof(USB_STR_n)
};

uint_8_ptr const g_string_descriptors[USB_MAX_STRING_DESCRIPTORS] =
{
    (uint_8_ptr const) USB_STR_0,
    (uint_8_ptr const) USB_STR_1,
    (uint_8_ptr const) USB_STR_2,
    (uint_8_ptr const) USB_STR_n
};

USB_ALL_LANGUAGES g_languages = 
{
    USB_STR_0, 
    sizeof(USB_STR_0),
    {
        {
            (uint_16 const)0x0409,
            (const uint_8 **)g_string_descriptors,
            g_string_desc_size
        }
    }
};

uint_8 const g_valid_config_values[USB_MAX_CONFIG_SUPPORTED+1]={0,1};

/****************************************************************************
 * Global Variables
 ****************************************************************************/
static uint_8 g_alternate_interface[USB_MAX_SUPPORTED_INTERFACES];

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Descriptor
 *
 * @brief The function returns the correponding descriptor
 *
 * @param controller_ID : Controller ID
 * @param type          : Type of descriptor requested
 * @param sub_type      : String index for string descriptor
 * @param index         : String descriptor language Id
 * @param descriptor    : Output descriptor pointer
 * @param size          : Size of descriptor returned
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             When Error
 *****************************************************************************
 * This function is used to pass the pointer of the requested descriptor
 *****************************************************************************/
uint_8 USB_Desc_Get_Descriptor(
    uint_8 controller_ID,   /* [IN]  Controller ID */
    uint_8 type,            /* [IN]  Type of descriptor requested */
    uint_8 str_num,         /* [IN]  String index for string descriptor */
    uint_16 index,          /* [IN]  String descriptor language Id */
    uint_8_ptr *descriptor, /* [OUT] Output descriptor pointer */
    USB_PACKET_SIZE *size   /* [OUT] Size of descriptor returned */
)
{
    UNUSED (controller_ID);
    switch(type)
    {
        case USB_REPORT_DESCRIPTOR:
        {
            type = USB_MAX_STD_DESCRIPTORS;
            *descriptor = (uint_8_ptr)g_std_descriptors [type];
            *size = g_std_desc_size[type];
        }
        break;
        case USB_AUDIO_DESCRIPTOR:
        {
            type = USB_CONFIG_DESCRIPTOR ;
            *descriptor = (uint_8_ptr)(g_std_descriptors [type]+
                CONFIG_ONLY_DESC_SIZE+IFACE_ONLY_DESC_SIZE);
            *size = AUDIO_ONLY_DESC_SIZE;
        }
        break;
        case USB_STRING_DESCRIPTOR:
        {
            if(index == 0)
            {
                /* return the string and size of all languages */
                *descriptor = (uint_8_ptr)g_languages.
                    languages_supported_string;
                *size = g_languages.languages_supported_size;
            } else
            {
                uint_8 lang_id=0;
                uint_8 lang_index=USB_MAX_LANGUAGES_SUPPORTED;

                for(;lang_id< USB_MAX_LANGUAGES_SUPPORTED;lang_id++)
                {
                    /* check whether we have a string for this language */
                    if(index == g_languages.usb_language[lang_id].language_id)
                    {   /* check for max descriptors */
                        if(str_num < USB_MAX_STRING_DESCRIPTORS)
                        {   /* setup index for the string to be returned */
                            lang_index=str_num;
                        }
                        break;
                    }

                }

                /* set return val for descriptor and size */
                *descriptor = (uint_8_ptr)g_languages.usb_language[lang_id].
                    lang_desc[lang_index];
                *size = g_languages.usb_language[lang_id].
                    lang_desc_size[lang_index];

            }
        }
        break;
        default :
            if (type < USB_MAX_STD_DESCRIPTORS)
            {
                /* set return val for descriptor and size*/
                *descriptor = (uint_8_ptr)g_std_descriptors [type];

                /* if there is no descriptor then return error */
                if(*descriptor == NULL)
                {
                    return USBERR_INVALID_REQ_TYPE;
                }

                *size = g_std_desc_size[type];
            }
            else /* invalid descriptor */
            {
                return USBERR_INVALID_REQ_TYPE;
            }
            break;
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Interface
 *
 * @brief The function returns the alternate interface
 *
 * @param controller_ID : Controller ID
 * @param interface     : Interface number
 * @param alt_interface : Output alternate interface
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             When Error
 *****************************************************************************
 *This function is called by the framework module to get the current interface
 *****************************************************************************/
uint_8 USB_Desc_Get_Interface(
    uint_8 controller_ID,     /* [IN] Controller ID */
    uint_8 interface,         /* [IN] Interface number */
    uint_8_ptr alt_interface  /* [OUT] Output alternate interface */
)
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get alternate interface*/
        *alt_interface = g_alternate_interface[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Interface
 *
 * @brief The function sets the alternate interface
 *
 * @param controller_ID : Controller ID
 * @param interface     : Interface number
 * @param alt_interface : Input alternate interface
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             When Error
 *****************************************************************************
 *This function is called by the framework module to set the interface
 *****************************************************************************/
uint_8 USB_Desc_Set_Interface(
    uint_8 controller_ID, /* [IN] Controller ID */
    uint_8 interface,     /* [IN] Interface number */
    uint_8 alt_interface  /* [IN] Input alternate interface */
)
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set alternate interface*/
        g_alternate_interface[interface] = alt_interface;
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Valid_Configation
 *
 * @brief The function checks whether the configuration parameter
 *        input is valid or not
 *
 * @param controller_ID : Controller ID
 * @param config_val    : Configuration value
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************
 * This function checks whether the configuration is valid or not
 *****************************************************************************/
boolean USB_Desc_Valid_Configation(
    uint_8 controller_ID,/*[IN] Controller ID */
    uint_16 config_val   /*[IN] Configuration value */
)
{
    uint_8 loop_index=0;    

    UNUSED (controller_ID);    
    /* check with only supported val right now */
    while(loop_index < (USB_MAX_CONFIG_SUPPORTED+1))
    {
        if(config_val == g_valid_config_values[loop_index])
        {
            return TRUE;
        }
        loop_index++;
    }
    return FALSE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Valid_Interface
 *
 * @brief The function checks whether the interface parameter
 *        input is valid or not
 *
 * @param controller_ID : Controller ID
 * @param interface     : Target interface
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************
 * This function checks whether the interface is valid or not
 *****************************************************************************/
boolean USB_Desc_Valid_Interface(
    uint_8 controller_ID, /*[IN] Controller ID */
    uint_8 interface      /*[IN] Target interface */
)
{
    uint_8 loop_index=0;
    UNUSED (controller_ID);
    /* check with only supported val right now */
    while(loop_index < USB_MAX_SUPPORTED_INTERFACES)
    {
        if(interface == g_alternate_interface[loop_index])
        {
            return TRUE;
        }
        loop_index++;
    }
    return FALSE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Remote_Wakeup
 *
 * @brief The function checks whether the remote wakeup is supported or not
 *
 * @param controller_ID : Controller ID
 *
 * @return REMOTE_WAKEUP_SUPPORT (TRUE) - If remote wakeup supported
 *****************************************************************************
 * This function returns remote wakeup is supported or not
 *****************************************************************************/
boolean USB_Desc_Remote_Wakeup(
    uint_8 controller_ID      /* [IN] Controller ID */
)
{
    UNUSED (controller_ID);
    return REMOTE_WAKEUP_SUPPORT;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Endpoints
 *
 * @brief The function returns with the list of all non control endpoints used
 *
 * @param controller_ID : Controller ID
 *
 * @return pointer to USB_ENDPOINTS
 *****************************************************************************
 * This function returns the information about all the non control endpoints
 * implemented
 *****************************************************************************/
void* USB_Desc_Get_Endpoints(
    uint_8 controller_ID      /* [IN] Controller ID */
)
{
    UNUSED (controller_ID);
    return (void*)&usb_desc_ep;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Audio_Entities
 *
 * @brief The function returns with the list of all Input Terminal,
 * Output Terminal and Feature Unit
 *
 * @param controller_ID : Controller ID
 *
 * @return pointer to USB_AUDIO_UNITS
 *****************************************************************************
 * This function returns the information about all the Input Terminal,
 * Output Terminal and Feature Unit
 *****************************************************************************/  
void* USB_Desc_Get_Audio_Entities(
    uint_8 controller_ID      /* [IN] Controller ID */
)
{
    UNUSED (controller_ID);
    return (void*)&usb_audio_unit;
}

uint_8 g_copy_protect[USB_MAX_SUPPORTED_INTERFACES]={0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Copy_Protect
 *
 * @brief  The function is called in response to Set Terminal Control Request
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return  USB_OK                  : When Successfull
 *          USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                    Interface is presented
 ******************************************************************************
 * This function is called to Set Copy Protect Level
 *****************************************************************************/
uint_8 USB_Desc_Set_Copy_Protect(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set copy protect data */
        g_copy_protect[interface] = **data;
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Copy_Protect
 *
 * @brief  The function is called in response to Get Terminal Control Request
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return  USB_OK                  : When Successfull
 *          USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                    Interface is presented
 ******************************************************************************
 * This function is called to Get Copy Protect Level
 *****************************************************************************/
uint_8 USB_Desc_Get_Copy_Protect(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{  
    UNUSED (controller_ID);
    UNUSED (size);

    /* If interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get copy protect data*/
        *size=1;
        *data=&g_copy_protect[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_mute[USB_MAX_SUPPORTED_INTERFACES] ={0x00};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Mute
 *
 * @brief  The function sets Current Mute state
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return    USB_OK                  : When Successfull
 *            USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                      Interface is presented
 ******************************************************************************
 * Sets current Mute state specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Mute (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data to be send */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{ 
    UNUSED (controller_ID);
    UNUSED (size);

    /* If interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set current mute data */
        g_cur_mute[interface] = **data;

#if (!(defined _MC9S08JS16_H))
        (void)printf("Mute: %d\r\n", g_cur_mute[interface]);
#endif

        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Mute
 *
 * @brief The function gets the current Mute state
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Mute state to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Mute(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED (controller_ID); 
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get current mute data */
        *size = 1;
        *data = &g_cur_mute[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_volume[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x00,0x80}};
uint_8 g_min_volume[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x00,0x80}};
uint_8 g_max_volume[USB_MAX_SUPPORTED_INTERFACES][2] = {{0xFF,0x7F}};
uint_8 g_res_volume[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x01,0x00}};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Volume
 *
 * @brief  The function sets Current Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return  USB_OK                  : When Successfull
 *          USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                    Interface is presented
 ******************************************************************************
 * Sets current Volume value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Volume (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{  
    int_16 volume;
    UNUSED (controller_ID);
    UNUSED (size);

    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set current volume data */
        g_cur_volume[interface][0] = **data;
        g_cur_volume[interface][1] = *(*data+1);
        volume = (int_16)((g_cur_volume[interface][1] << 8) | g_cur_volume[interface][0]);
        /* The current volume is received as logical value 
         * Logical  S16:  0x8000      to 0x7FFF             and corresponds to
         * Physical      -127.9661 dB to 127.9661 dB
         * The equation for the line that passes through the above coordinates results:
         *  y = 0.0039*x - 3.1    
         */
#if (!(defined _MC9S08JS16_H))
        {
            int_16 volPhysical;
            if((uint_16)volume == 0x8000)
            {
                (void)printf("Volume: Silence\r\n");	    		
            }
            else
            {
                volPhysical = (int_16)((int_16)(((int_32)volume * 4) / 1000) - 3);
                (void)printf("Volume: %d dB\r\n", volPhysical);
            }

        }
#endif

        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Volume
 *
 * @brief  The function sets Minimum Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minimum Volume value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Min_Volume(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data to send */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{ 
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set min volume data */
        g_min_volume[interface][0] = **data;
        g_min_volume[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Max_Volume
 *
 * @brief  The function sets Maximum Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Volume value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Max_Volume (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{  
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set max volume data */
        g_max_volume[interface][0] = **data;
        g_max_volume[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Volume
 *
 * @brief  The function sets Resolution Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Volume value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Volume(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{ 
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set resolution volume data */
        g_res_volume[interface][0] = **data;
        g_res_volume[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Volume
 *
 * @brief  The function gets the Current Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Volume value to the Host
 *****************************************************************************/    

uint_8 USB_Desc_Get_Cur_Volume(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get current volume data */
        *size = 2;
        *data = g_cur_volume[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Volume
 *
 * @brief  The function gets the Minimum Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Min Volume value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Volume(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get min volume data */
        *size = 2;
        *data = g_min_volume[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Volume
 *
 * @brief  The function gets the Maximum Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Max Volume value to the Host
 *****************************************************************************/        
uint_8 USB_Desc_Get_Max_Volume (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get max volume data */
        *size = 2;
        *data = g_max_volume[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Volume
 *
 * @brief  The function gets the Resolution Volume value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Volume value to the Host
 *****************************************************************************/        
uint_8 USB_Desc_Get_Res_Volume(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES) 
    {
        /* Get resolution volume data*/
        *size = 2;
        *data = g_res_volume[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_bass[USB_MAX_SUPPORTED_INTERFACES] = {0x00};
uint_8 g_min_bass[USB_MAX_SUPPORTED_INTERFACES] = {0x80};
uint_8 g_max_bass[USB_MAX_SUPPORTED_INTERFACES] = {0x7F};
uint_8 g_res_bass[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Bass
 *
 * @brief  The function sets Current Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Bass value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set current bass data */
        g_cur_bass[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Bass
 *
 * @brief  The function sets Minimum Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minimum Bass value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Min_Bass(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set min bass data */
        g_min_bass[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Bass
 *
 * @brief  The function sets Maximum Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Bass value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Max_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set max bass data */
        g_max_bass[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Bass
 *
 * @brief  The function sets Resolution Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Bass value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Set resolution bass data */
        g_res_bass[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Bass
 *
 * @brief  The function gets the Current Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Bass value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID); 
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get current bass data */
        *size = 1;
        *data = &g_cur_bass[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Bass
 *
 * @brief  The function gets the Minimum Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Bass value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Bass(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* Get min bass data */
        *size = 1;
        *data = &g_min_bass[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Bass
 *
 * @brief  The function gets the Maximum Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Bass value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get max bass data */
        *size = 1;
        *data = &g_max_bass[interface];
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Bass
 *
 * @brief  The function gets the Resolution Bass value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Bass value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Bass (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get resolution bass data */
        *size = 1;
        *data = &g_res_bass[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_mid[USB_MAX_SUPPORTED_INTERFACES] = {0x00};
uint_8 g_min_mid[USB_MAX_SUPPORTED_INTERFACES] = {0x80};
uint_8 g_max_mid[USB_MAX_SUPPORTED_INTERFACES] = {0x7F};
uint_8 g_res_mid[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Mid
 *
 * @brief  The function sets Current Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Mid value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Mid(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set current mid data */
        g_cur_mid[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Mid
 *
 * @brief  This function is called to Set Minimum Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minumum Mid value specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Min_Mid(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set min mid data*/
        g_min_mid[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Mid
 *
 * @brief  This function is called to Set Maximum Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Mid value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Max_Mid(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set max mid data*/
        g_max_mid[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Mid
 *
 * @brief  This function is called to Set Resolution Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Mid value specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Res_Mid(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set resolution mid data*/
        g_res_mid[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Mid
 *
 * @brief  The function gets the Current Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Mid value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Mid (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current Mid data*/
        *size = 1;
        *data=&g_cur_mid[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Mid
 *
 * @brief  The function gets the Minimum Mid value
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Mid value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Mid (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface<USB_MAX_SUPPORTED_INTERFACES){
        /* get min mid data data*/
        *size = 1;
        *data = &g_min_mid[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Mid
 *
 * @brief  The function gets the Maximum Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Mid value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Mid (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface<USB_MAX_SUPPORTED_INTERFACES){
        /* get max mid data data*/
        *size = 1;
        *data = &g_max_mid[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Mid
 *
 * @brief  The function gets the Resolution Mid value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Mid value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Mid (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface<USB_MAX_SUPPORTED_INTERFACES){
        /* get resolution mid data data*/
        *size = 1;
        *data = &g_res_mid[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_treble[USB_MAX_SUPPORTED_INTERFACES] = {0x01};
uint_8 g_min_treble[USB_MAX_SUPPORTED_INTERFACES] = {0x80};
uint_8 g_max_treble[USB_MAX_SUPPORTED_INTERFACES] = {0x7F};
uint_8 g_res_treble[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Treble
 *
 * @brief  The function set Current Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Treble value specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Cur_Treble(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current treble data*/
        g_cur_treble[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Treble
 *
 * @brief  This function set Minimum Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minimum Treble value specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Min_Treble(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set min treble data*/
        g_min_treble[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Treble
 *
 * @brief  The function set Maximum Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Treble value specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Max_Treble(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set max treble data*/
        g_max_treble[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Treble
 *
 * @brief  The function set Resolution Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Treble value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Treble(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set resolution treble data*/
        g_res_treble[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Treble
 *
 * @brief  The function get Current Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Treble value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Treble (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{  
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current treble data*/
        *size=1;
        *data=&g_cur_treble[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Treble
 *
 * @brief  The function get Minimum Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Treble value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Treble (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get min treble data*/
        *size=1;
        *data=&g_min_treble[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Treble
 *
 * @brief  The function get Maximum Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Treble value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Treble (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get max treble data*/
        *size=1;
        *data=&g_max_treble[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Treble
 *
 * @brief  The function gets Resolution Treble value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Treble value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Treble (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get resolution treble data*/
        *size=1;
        *data=&g_res_treble[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_graphic_equalizer[USB_MAX_SUPPORTED_INTERFACES][5] = {{0x00,0x00,0x00,0x00,0x00}};
uint_8 g_min_graphic_equalizer[USB_MAX_SUPPORTED_INTERFACES][5] = {{0x00,0x00,0x00,0x00,0x00}};
uint_8 g_max_graphic_equalizer[USB_MAX_SUPPORTED_INTERFACES][5] = {{0x00,0x00,0x00,0x00,0x00}};
uint_8 g_res_graphic_equalizer[USB_MAX_SUPPORTED_INTERFACES][5] = {{0x00,0x00,0x00,0x00,0x00}};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Graphic_Equalizer
 *
 * @brief  The function sets Current Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Graphic Equalizer values specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Graphic_Equalizer(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{  
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current graphic equalizer data*/
        g_cur_graphic_equalizer[interface][0] = **data;
        g_cur_graphic_equalizer[interface][1] = *(*data+1);
        g_cur_graphic_equalizer[interface][2] = *(*data+2);
        g_cur_graphic_equalizer[interface][3] = *(*data+3);
        g_cur_graphic_equalizer[interface][4] = *(*data+4);
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Graphic_Equalizer
 *
 * @brief  The function sets Minimum Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minimum Graphic Equalizer values specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Min_Graphic_Equalizer(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set min graphic equalizer data*/
        g_min_graphic_equalizer[interface][0] = **data;
        g_min_graphic_equalizer[interface][1] = *(*data+1);
        g_min_graphic_equalizer[interface][2] = *(*data+2);
        g_min_graphic_equalizer[interface][3] = *(*data+3);
        g_min_graphic_equalizer[interface][4] = *(*data+4);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Graphic_Equalizer
 *
 * @brief  The function sets Maximum Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Graphic Equalizer values specified by the Host
 *****************************************************************************/ 
uint_8 USB_Desc_Set_Max_Graphic_Equalizer(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set max graphic equalizer data*/
        g_max_graphic_equalizer[interface][0] = **data;
        g_max_graphic_equalizer[interface][1] = *(*data+1);
        g_max_graphic_equalizer[interface][2] = *(*data+2);
        g_max_graphic_equalizer[interface][3] = *(*data+3);
        g_max_graphic_equalizer[interface][4] = *(*data+4);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Graphic_Equalizer
 *
 * @brief  The function sets Resolution Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Graphic Equalizer values specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Graphic_Equalizer(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set resolution graphic equalizer data*/
        g_res_graphic_equalizer[interface][0] = **data;
        g_res_graphic_equalizer[interface][1] = *(*data+1);
        g_res_graphic_equalizer[interface][2] = *(*data+2);
        g_res_graphic_equalizer[interface][3] = *(*data+3);
        g_res_graphic_equalizer[interface][4] = *(*data+4);
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Graphic_Equalizer
 *
 * @brief  The function gets Current Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Graphic Equalizer values to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Graphic_Equalizer (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current graphic equalizer data*/
        *size=5;
        *data=g_cur_graphic_equalizer[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Graphic_Equalizer
 *
 * @brief  The function gets Minimum Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Graphic Equalizer values to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Graphic_Equalizer (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get min graphic equalizer data*/
        *size=5;
        *data=g_min_graphic_equalizer[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Graphic_Equalizer
 *
 * @brief  The function gets Maximum Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Graphic Equalizer values to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Graphic_Equalizer (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{

    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get max graphic equalizer data*/
        *size=5;
        *data=g_max_graphic_equalizer[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Graphic_Equalizer
 *
 * @brief  The function gets Resolution Graphic Equalizer values
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Graphic Equalizer values to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Graphic_Equalizer (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get resolution graphic equalizer data*/
        *size=5;
        *data=g_res_graphic_equalizer[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_automatic_gain[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Automatic_Gain
 *
 * @brief  The function sets Current Automatic Gain value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Automatic Gain value specified by the Host
 *****************************************************************************/

uint_8 USB_Desc_Set_Cur_Automatic_Gain(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current automatic data*/
        g_cur_automatic_gain[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Automatic_Gain
 *
 * @brief  The function gets Current Automatic Gain value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Automatic Gain value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Automatic_Gain(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current automatic data*/
        *size=1;
        *data=&g_cur_automatic_gain[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_delay[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x00,0x40}};
uint_8 g_min_delay[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x00,0x00}};
uint_8 g_max_delay[USB_MAX_SUPPORTED_INTERFACES][2] = {{0xFF,0xFF}};
uint_8 g_res_delay[USB_MAX_SUPPORTED_INTERFACES][2] = {{0x00,0x01}};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Delay
 *
 * @brief  The function sets Current Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Current Delay value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current delay data*/
        g_cur_delay[interface][0] = **data;
        g_cur_delay[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Delay
 *
 * @brief  The function sets Minimum Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Minimum Delay value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Min_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set min delay data*/
        g_min_delay[interface][0] = **data;
        g_min_delay[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Delay
 *
 * @brief  The function sets Maximum Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Maximum Delay value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Max_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set max delay data*/
        g_max_delay[interface][0] = **data;
        g_max_delay[interface][1] = *(*data+1);

        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Delay
 *
 * @brief  The function sets Resolution Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Resolution Delay value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set resolution delay data*/
        g_res_delay[interface][0] = **data;
        g_res_delay[interface][1] = *(*data+1);
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Delay
 *
 * @brief  The function gets Current Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Delay value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current delay data*/
        *size=2;
        *data=g_cur_delay[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Delay
 *
 * @brief  The function gets Minimum Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Delay value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get min delay data*/
        *size=2;
        *data=g_min_delay[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Delay
 *
 * @brief  The function gets Maximum Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Delay value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get max delay data*/
        *size=2;
        *data=g_max_delay[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Delay
 *
 * @brief  The function gets Resolution Delay value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Delay value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Delay(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get resolution delay data*/
        *size=2;
        *data=g_res_delay[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_bass_boost[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Bass_Boost
 *
 * @brief  The function sets Current Bass Boost value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Current Bass Boost value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Bass_Boost(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{  
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current bass boost data*/
        g_cur_bass_boost[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Bass_Boost
 *
 * @brief  The function gets Current Bass Boost value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Bass Boost value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Bass_Boost(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current bass boost data*/
        *size=1;
        *data=&g_cur_bass_boost[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

uint_8 g_cur_loudness[USB_MAX_SUPPORTED_INTERFACES] = {0x01};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Loudness
 *
 * @brief  The function sets Current Loudness value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Set Current Loudness value specified to the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Loudness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* set current loudness data*/
        g_cur_loudness[interface] = **data;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Loudness
 *
 * @brief  The function gets Current Loudness value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Loudness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Loudness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES){
        /* get current loudness data*/
        *size=1;
        *data=&g_cur_loudness[interface];
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

#if AUDIO_CLASS_2_0
uint_8 g_cur_sampling_frequency[4] = {0x00,0x00,0x00,0x01};
uint_8 g_min_sampling_frequency[4] = {0x00,0x00,0x00,0x00};
uint_8 g_max_sampling_frequency[4] = {0xFF,0xFF,0xFF,0xFF};
uint_8 g_res_sampling_frequency[4] = {0x00,0x00,0x01,0x00};
#else
uint_8 g_cur_sampling_frequency[3] = {0x00,0x00,0x01};
uint_8 g_min_sampling_frequency[3] = {0x00,0x00,0x00};
uint_8 g_max_sampling_frequency[3] = {0x7F,0xFF,0xFF};
uint_8 g_res_sampling_frequency[3] = {0x00,0x01,0x00};
#endif /* AUDIO_CLASS_2_0 */

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Sampling_Frequency
 *
 * @brief  The function sets Current Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Sampling Frequency value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    UNUSED (interface);

    /* set current sampling fequency data*/
    g_cur_sampling_frequency[0] = **data;
    g_cur_sampling_frequency[1] = *(*data+1);
    g_cur_sampling_frequency[2] = *(*data+2);
#if AUDIO_CLASS_2_0
    g_cur_sampling_frequency[3] = *(*data+3);
#endif /* AUDIO_CLASS_2_0 */

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Min_Sampling_Frequency
 *
 * @brief  The function sets Minimum Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Minimum Sampling Frequency value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Min_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    UNUSED (interface);
    /* set min sampling frequency data*/
    g_min_sampling_frequency[0] = **data;
    g_min_sampling_frequency[1] = *(*data+1);
    g_min_sampling_frequency[2] = *(*data+2);
#if AUDIO_CLASS_2_0
    g_min_sampling_frequency[3] = *(*data+3);
#endif /* AUDIO_CLASS_2_0 */

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Max_Sampling_Frequency
 *
 * @brief  The function sets Maximum Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Maximum Sampling Frequency value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Max_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    UNUSED (interface);
    /* set max sampling frequency data*/
    g_max_sampling_frequency[0] = **data;
    g_max_sampling_frequency[1] = *(*data+1);
    g_max_sampling_frequency[2] = *(*data+2);
#if AUDIO_CLASS_2_0
    g_max_sampling_frequency[3] = *(*data+3);
#endif /* AUDIO_CLASS_2_0 */

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Res_Sampling_Frequency
 *
 * @brief  The function sets Resolution Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Resolution Sampling Frequency value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Res_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    UNUSED (interface);
    /* set resolution sampling frequency data*/
    g_res_sampling_frequency[0] = **data;
    g_res_sampling_frequency[1] = *(*data+1);
    g_res_sampling_frequency[2] = *(*data+2);
#if AUDIO_CLASS_2_0
    g_cur_sampling_frequency[3] = *(*data+3);
#endif /* AUDIO_CLASS_2_0 */

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Sampling_Frequency
 *
 * @brief  The function gets Current Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Sampling Frequency value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    /* get current sampling frequency data*/
#if AUDIO_CLASS_2_0
    *size=4;
#else
    *size=3;
#endif /* AUDIO_CLASS_2_0 */
    *data=g_cur_sampling_frequency;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Sampling_Frequency
 *
 * @brief  The function gets Minimum Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Minimum Sampling Frequency value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    /* get min sampling frequency data*/
#if AUDIO_CLASS_2_0
    *size=4;
#else
    *size=3;
#endif /* AUDIO_CLASS_2_0 */
    *data=g_min_sampling_frequency;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Sampling_Frequency
 *
 * @brief  The function gets Maximum Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Maximum Sampling Frequency value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    /* get max sampling frequency data*/
#if AUDIO_CLASS_2_0
    *size=4;
#else
    *size=3;
#endif /* AUDIO_CLASS_2_0 */
    *data=g_max_sampling_frequency;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Sampling_Frequency
 *
 * @brief  The function gets Resolution Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Resolution Sampling Frequency value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Sampling_Frequency(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    /* get resolution sampling frequency data*/
#if AUDIO_CLASS_2_0
    *size=4;
#else
    *size=3;
#endif /* AUDIO_CLASS_2_0 */
    *data=g_res_sampling_frequency;
    return USB_OK;
}

uint_8 g_cur_pitch = 0x01;

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Pitch
 *
 * @brief  The function sets Current Pitch value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets Current Pitch value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Pitch(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (size);
    UNUSED (interface);
    /* set current pitch data*/
    g_cur_pitch = **data;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Pitch
 *
 * @brief  The function gets Current Pitch value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Pitch value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Pitch(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    /* get current pitch data*/
    *size=1;
    *data=&g_cur_pitch;
    return USB_OK;
}

#if AUDIO_CLASS_2_0
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Clock_Validity
 *
 * @brief  The function gets Current Sampling Frequency value
 *
 * @param controller_ID   : Controller ID
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns Current Clock state to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Clock_Validity(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
) 
{
    uint_8 val = TRUE;

    UNUSED (controller_ID);
    UNUSED (interface);

    *size = 1;
    *data = &val;
    return USB_OK;
}
#endif /* AUDIO_CLASS_2_0 */

uint_8 status_endpoint_data[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Mem_Endpoint
 *
 * @brief  The function gets endpoint memory value
 *
 * @param controller_ID   : Controller ID
 * @param offset          : Offset
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns endpoint memory value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Mem_Endpoint(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_16 offset,                     /* [IN] Offset */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    uint_16 index;

    UNUSED (controller_ID);
    UNUSED (interface);

    for(index = 0; index < *size ; index++) 
    {   /* copy the report sent by the host */          
        status_endpoint_data[offset + index] = *(*data + index);
    }
    *size = 0;     

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Mem_Endpoint
 *
 * @brief  The function gets endpoint memory value
 *
 * @param controller_ID   : Controller ID
 * @param offset          : Offset
 * @param interface       : Interface
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return :
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns endpoint memory value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Mem_Endpoint(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_16 offset,                     /* [IN] Offset */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
) 
{
    UNUSED (controller_ID);
    UNUSED (interface);
    UNUSED (size);

    *data = &status_endpoint_data[offset];
    return USB_OK;
}
/* EOF */
