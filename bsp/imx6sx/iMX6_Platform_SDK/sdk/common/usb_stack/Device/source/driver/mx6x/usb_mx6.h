/*
 * Copyright (C) 2009-2010, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
*/

#ifndef __USB_MX28_H

#define __USB_MX28_H

//#include "datatypes.h"

#include "sdk_types.h"
#include "registers/regsusbcore.h"
#include "registers/regsusbnoncore.h"
#include "registers/regsusbanalog.h"
#include "registers/regsusbphy.h"

// #include "mx28.h"

// #include "mx28_regsusbctrl.h"
// 
// #include "mx28_regsusbphy.h"
// 
// #include "usb_ch9.h"



typedef uint8_t bool_8;

#define MAX_USB_STACKS                  2

#define USB_MAX_DEVICE_ADDR 		127

#define USB_DEFAULT_ADDR            0x00

#define USB_DEV_VALUE_OF_UNCONFIG   0x0

typedef enum {
    USB_IDEL = 0,
    USB_MODE_DEVICE = 2,
    USB_MODE_HOST = 3,
    USB_MODE_UNKNOW,

} usb_mode_t;

///////////////////////////////////////////////////////////////////

/***********************usb_descriptor_definitions*************************/

#define VID	0x15A2

#define	PID	0x004F

/* String SUB DESCRIPTOR type */

#define STR_DES0		0x0

#define STR_DES1		0x1

#define STR_DES2		0x2

#define STR_DES3		0x3

#define STR_DES4		0x4

#define STR_DES5		0x5

/* Constants defined to represent device descriptor elements. */

#define USB_DEV_DESC_LEN                                 0x12

#define USB_DEV_DESC_TYPE                                0x01

#define USB_DEV_DESC_SPEC_LB                             0x00

#define USB_DEV_DESC_SPEC_HB                             0x02

#define USB_DEV_DESC_SPEC                                (0xFFFF&0x0200)

#define USB_DEV_DESC_DEV_CLASS                           0x00  /*ROM Code definition*/  //0x02    /* Fisher: CDC bDeviceClass */

#define USB_DEV_DESC_DEV_SUBCLASS						 0x00   //0x02  /* Fisher: Abstract Control Model*/

#define USB_DEV_DESC_DEV_PROTOCOL                        0x00

#define USB_DEV_DESC_EP0_MAXPACKETSIZE                   0x40

#define USB_DEV_DESC_VENDORID_LB                         (VID & 0x00FF)

#define USB_DEV_DESC_VENDORID_HB                         ((VID & 0xFF00) >> 0x8)

#define USB_DEV_DESC_VENDORID                            (0xFFFF&VID)

#define USB_DEV_DESC_PRODUCTID_LB                        (PID & 0x00FF)

#define USB_DEV_DESC_PRODUCTID_HB                        ((PID & 0xFF00) >> 0x8)

#define USB_DEV_DESC_PRODUCTID                           (0xFFFF&PID)

#define USB_DEV_DESC_DEV_RELEASE_NUM_LB                  0x01

#define USB_DEV_DESC_DEV_RELEASE_NUM_HB                  0x00

#define USB_DEV_DESC_DEV_RELEASE_NUM                     (0xFFFF&0x0001)

#define USB_DEV_DESC_DEV_STRING_IND_MANUFACTURE          0x01

#define USB_DEV_DESC_DEV_STRING_IND_PRODUCT              0x02

#define USB_DEV_DESC_DEV_STRING_IND_SERIAL_NUM           0x05   /*for mass storage device, it must >0 */

#define USB_DEV_DESC_DEV_NUM_CONFIGURATIONS              0x01

/* Constants defindes to represent elements of configuration descriptor. */

#define USB_DEV_CONFIG_DESC_LEN                          0x09   /* Length of configuration descriptor. */

#define USB_DEV_CONFIG_DESC_TYPE                         0x02   /* Descriptor type. */

#define USB_DEV_CONFIG_DESC_TTL_LEN_LB                   0x20   /* Total length of configuration information. */

#define USB_DEV_CONFIG_DESC_TTL_LEN_HB                   0x00   /* Total length of configuration information. */

#define USB_DEV_CONFIG_DESC_TOTAL_LENGTH                 (0xFFFF&0x0020)

#define USB_DEV_CONFIG_DESC_NUM_OF_INF                   0x01   /* Number of interfaces in this configuration. */

#define USB_DEV_CONFIG_DESC_CONFIG_VALUE                 0x01   /* Configuration value. */

#define USB_DEV_CONFIG_DESC_STRING_INDEX                 0x00   /* String index for this configuration. */

#define USB_DEV_CONFIG_DESC_ATTRIBUTES                   0xC0   /*  Self powered and supported remote wakeup. */

    /* 0x80 Self powered and supported remote wakeup. */

#define USB_DEV_CONFIG_DESC_MAX_POWER                    0x32   /* 100ma,Max power consumed by phone. */

#define USB_DEV_INF_DESC_LEN                             0x09   /* Interface descriptor length. */

#define USB_DEV_INF_DESC_TYPE                            0x04   /* The descriptor type, 4 interface descriptor. */

#define USB_DEV_INF_DESC_INF_INDEX                       0x00   /* Interface index. */

#define USB_DEV_INF_DESC_ALT_SETTING                     0x00   /* The alternate setting is 0. */

#define USB_DEV_INF_DESC_NUM_OF_EP                       0x02   /* Control endpoint and data endpoint 1 and 2. */

#define USB_DEV_INF_DESC_INF_CLASS_VENDOR                0xFF   /* Interface class: Vendor Specific. */

#define USB_DEV_INF_DESC_INF_CLASS_MSC                   0x08   /* Interface class: Mass Storage. */

#define USB_DEV_INF_DESC_INF_SUBCLASS_S_BLANK            0x40   /* (Subclass) Motorola Flash Download. */

#define USB_DEV_INF_DESC_INF_SUBCLASS_NS_BLANK           0x42

#define USB_DEV_INF_DESC_INF_SUBCLASS_MSC_SCSI           0x06   /* SCSI transparent command set for mass storage */

#define USB_DEV_INF_DESC_INF_PROTOCOL                    0x01   /* (Interface protocol) Vendor Specific, ROM bootloader interface. */

#define USB_DEV_INF_DESC_INF_PROTOCOL_MSC_BOT            0x50   /* Mass Storage Bulk Only Transport */

#define USB_DEV_INF_DESC_STRING_INDEX                    0x04   /* Index of interface string descriptor. */

/* Constants defined to represent the endpoint descriptor elements. */

#define USB_MAX_PACKET_SIZE			0x0200

#define USB_MAX_PACKET_SIZE_LO		(USB_MAX_PACKET_SIZE&0xFF)

#define USB_MAX_PACKET_SIZE_HI		((USB_MAX_PACKET_SIZE>>8)&0xFF)

/* Endpoint 1 descriptor. */

#define USB_EP1_DESC_SIZE                                0x07   /* Size of descriptor in bytes. */

#define USB_EP1_DESC_TYPE                                0x05   /* Descriptor type. */

#define USB_EP1_DESC_EP_ADDR                             0x01   /* (Endpoint address) Endpoint 1, OUT. */

#define USB_EP1_DESC_ATTRIBUTES                          0x02   /* (Attributes) Bulk Endpoint. */

#define USB_EP1_DESC_MAX_PACKET_SIZE_FS_LB               0x40   /* Max Packet Size. */

#define USB_EP1_DESC_MAX_PACKET_SIZE_FS_HB               0x00   /* Max Packet Size. */

#define USB_EP1_DESC_MAX_PACKET_SIZE_HS_LB               USB_MAX_PACKET_SIZE_LO /* Max Packet Size. */

#define USB_EP1_DESC_MAX_PACKET_SIZE_HS_HB               USB_MAX_PACKET_SIZE_HI /* Max Packet Size. */

#define USB_EP1_DESC_MAX_PACKET_SIZE_HS                  (0xFFFF&USB_MAX_PACKET_SIZE)

#define USB_EP1_DESC_INTERVAL                            0x00   /* Interval, ignored. */

#define USB_EP1_DESC_INTERVAL_HS                      	 0x01   /* at most 1NAK. */

/* Endpoint 2 descriptor. */

#define USB_EP2_DESC_SIZE                                0x07   /* Size of descriptor in bytes. */

#define USB_EP2_DESC_TYPE                                0x05   /* Descriptor type. */

#define USB_EP2_DESC_EP_ADDR                             0x82   /* (Endpoint address) Endpoint 2, IN. */

#define USB_EP2_DESC_ATTRIBUTES                          0x02   /* (Attributes) Bulk Endpoint. */

#define USB_EP2_DESC_MAX_PACKET_SIZE_FS_LB               0x40   /* Max Packet Size. */

#define USB_EP2_DESC_MAX_PACKET_SIZE_FS_HB               0x00   /* Max Packet Size. */

#define USB_EP2_DESC_MAX_PACKET_SIZE_HS_LB               USB_MAX_PACKET_SIZE_LO /* Max Packet Size. */

#define USB_EP2_DESC_MAX_PACKET_SIZE_HS_HB               USB_MAX_PACKET_SIZE_HI /* Max Packet Size. */

#define USB_EP2_DESC_MAX_PACKET_SIZE_HS                  (0xFFFF&USB_MAX_PACKET_SIZE)

#define USB_EP2_DESC_INTERVAL                             0x00  /* Interval, ignored. */

#define USB_EP2_DESC_INTERVAL_HS                          0x01  /* at most 1NAK. */

/* String Descriptor 0 */

#define USB_STR0_DESC_SIZE                                0x04  /* Size of descriptor in bytes. */

#define USB_STR0_DESC_TYPE                                0x03  /* Descriptor type. */

#define USB_LANGUAGE_ID_LB                                0x09  /* Language id of english */

#define USB_LANGUAGE_ID_HB                                0x04  /* Language id of english */

/* String Descriptor 1 */

#define USB_STR1_DESC_SIZE                                0x3A  /* Size of descriptor in bytes. */

#define USB_STR1_DESC_TYPE                                0x03  /* Descriptor type. */

/* String Descriptor 2 */

#define USB_STR2_DESC_SIZE_NS                             0x20  /* Size of descriptor in bytes for Non Secure Download */

#define USB_STR2_DESC_SIZE_SE                             0x20  /* Size of descriptor in bytes for Secure Engg. download */

#define USB_STR2_DESC_SIZE_S                              0x20  /* Size of descriptor in bytes for Secure production download */

#define USB_STR2_DESC_TYPE                                0x03  /* Descriptor type. */

/* String Descriptor 3 */

#define USB_STR3_DESC_SIZE                                0x20  /* Size of descriptor in bytes. */

#define USB_STR3_DESC_TYPE                                0x03  /* Descriptor type. */

/* Serial number string descriptor */

#define USB_SN_DESC_LEN		   							  0x1A  /* Size of descriptor length */

#define USB_SN_DESC_TYPE								  0x03  /* type of descriptor */

/* USB string Descriptor structure 0 according to USB2.0 Specification */

typedef struct {
    unsigned char length;
    unsigned char descriptor_type;
    unsigned char language_id0_l;
    unsigned char language_id0_h;
} usb_str0_desc_t;

/* USB string Descriptor structure 1 according to USB2.0 Specification */

typedef struct {

    unsigned char length;

    unsigned char descriptor_type;

    unsigned char string[56];

} usb_str1_desc_t;

/* USB string Descriptor structure 2 according to USB2.0 Specification */

typedef struct {

    unsigned char length;

    unsigned char descriptor_type;

    unsigned char string[34];

} usb_str2_desc_t;

/* USB string Descriptor structure 3 according to USB2.0 Specification */

typedef struct {

    unsigned char length;

    unsigned char descriptor_type;

    unsigned char string[30];

} usb_str3_desc_t;

/* USB device serial number for mass storage requiremen*/

typedef struct {

    unsigned char length;

    unsigned char descriptor_type;

    unsigned char string[24];

} usb_str4_desc_t;

typedef struct dqh_setup_t {

    unsigned int dqh_word0;

    unsigned int dqh_word1;

    unsigned int dqh_word2;

    unsigned int dqh_word3;

    unsigned int dqh_word4;

    unsigned int dqh_word5;

    unsigned int dqh_word6;

    unsigned int dqh_word7;

    unsigned int dqh_word8;

    unsigned int dqh_word9;

    unsigned int dqh_word10;

    unsigned int dqh_word11;

} dqh_setup_t;

typedef struct dtd_setup_t {

    unsigned int dtd_word0;

    unsigned int dtd_word1;

    unsigned int dtd_word2;

    unsigned int dtd_word3;

    unsigned int dtd_word4;

    unsigned int dtd_word5;

    unsigned int dtd_word6;

    unsigned int dtd_word7;

} dtd_setup_t;

typedef struct dqh_t {

    unsigned int dqh_base;

    unsigned int next_link_ptr;

    unsigned int buffer_ptr0;

    unsigned int buffer_ptr1;

    unsigned int buffer_ptr2;

    unsigned int buffer_ptr3;

    unsigned int buffer_ptr4;

    unsigned short total_bytes;

    unsigned short mps;

    unsigned short current_offset;

    unsigned char zlt;

    unsigned char ios;

    unsigned char terminate;

    unsigned char ioc;

    unsigned char status;

	unsigned char mult;

} dqh_t;

typedef struct dtd_t {

    unsigned int dtd_base;

    unsigned int next_link_ptr;

    unsigned int buffer_ptr0;

    unsigned int buffer_ptr1;

    unsigned int buffer_ptr2;

    unsigned int buffer_ptr3;

    unsigned int buffer_ptr4;

    unsigned short total_bytes;

    unsigned short current_offset;

    unsigned char terminate;

    unsigned char ioc;

    unsigned char status;

} dtd_t;

typedef struct {

    unsigned int ep_dqh_base_addrs; /* Base Address of Queue Header */

    unsigned int ep_dtd_base_addrs; /* Base Address of Transfer Descriptor */

    unsigned int ep0_buffer_addrs;  /* Buffer Addres for EP0 IN  */

    unsigned int buffer1_address;   /* Buffer1 address for bulk transfer */

    unsigned int buffer1_status;    /* Status of Buffer1 */

    unsigned int buffer2_address;   /* Buffer2 address for bulk transfer */

    unsigned int buffer2_status;    /* Status of Buffer2 */

} buffer_map_t;

#define BIT0 	0x00000001

#define BIT1 	0x00000002

#define BIT2 	0x00000004

#define BIT3 	0x00000008

#define BIT4	0x00000010

#define BIT5 	0x00000020

#define BIT6	0x00000040

#define BIT7	0x00000080

#define BIT8	0x00000100

#define BIT9 	0x00000200

#define BIT10 	0x00000400

#define BIT11 	0x00000800

#define BIT12 	0x00001000

#define BIT13 	0x00002000

#define BIT14 	0x00004000

#define BIT15 	0x00008000

#define BIT16 	0x00010000

#define BIT17 	0x00020000

#define BIT18 	0x00040000

#define BIT19 	0x00080000

#define BIT20 	0x00100000

#define BIT21 	0x00200000

#define BIT22 	0x00400000

#define BIT23 	0x00800000

#define BIT24 	0x01000000

#define BIT25 	0x02000000

#define BIT26 	0x04000000

#define BIT27 	0x08000000

#define BIT28 	0x10000000

#define BIT29 	0x20000000

#define BIT30 	0x40000000

#define BIT31 	0x80000000

/* Device Queue Head and Device Transfer Descriptor Related Defination */

#define SIZE_OF_QHD     0x40

#define SIZE_OF_DTD0    0x20

#define SIZE_OF_DTD1    0x20

#define dTD_SIZE_EPIN   (SIZE_OF_DTD0 + SIZE_OF_DTD1)   //0x40

#define dTD_SIZE_EPOUT  (SIZE_OF_DTD0 + SIZE_OF_DTD1)   //0x40

#define BUFFER_USED_PER_EP ((SIZE_OF_QHD + dTD_SIZE_EPIN) +(SIZE_OF_QHD + dTD_SIZE_EPOUT))  //0x100

#define ZLT_ENABLE      0

#define ZLT_DISABLE     1

#define IOS_NOTSET      0

#define IOS_SET         1

#define IOC_NOTSET      0

#define IOC_SET         1

#define TERMINATE       1

#define NOT_TERMINATE   0

#define NO_STATUS       0

#define ACTIVE          BIT7

#define EPOUT_COMPLETE  BIT0

#define EPIN_COMPLETE   BIT16

#define EPOUT_PRIME     BIT0

#define EPIN_PRIME      BIT16

#define EPOUT_ENABLE    BIT7

#define EPIN_ENABLE     BIT23

#define STALL_RX        0x00000001

#define STALL_TX        0x00010000

/* Maximum packet size defination */

#define MPS_8	8

#define MPS_64	64

/* enum for endpoint numbers */

enum {
    EP0,
    EP1,
    EP2,
    EP3,
    EP4,
    EP5
};

enum {
    OUT,
    IN
};

/* enum for data transfer type on endpoints */

enum {
    CONTROL,
    ISOCHRONOUS,
    BULK,
    INTERRUPT
};

/* Status of all transaction on USB */

enum {
    USB_SUCCESS,
    USB_FAILURE,
    USB_INVALID = -1            /* Always Keep this entry in last */
};

typedef int usb_status_t;

/* USB Device State which are handled by DCD */

typedef enum {
    USB_DEV_DUMMY_STATE,
    USB_DEV_DEFAULT_STATE,
    USB_DEV_ADDRESSED_STATE,

    USB_DEV_CONFIGURED_STATE
} usb_state_t;

/* USB Device Setup Packet which is handled by USB device driver during enumeration */

typedef union {

    unsigned char byte[8];

    usb_standard_device_request_t fields;

} usb_setup_packet_t;

#define USB_DEVICE

typedef struct usb_mx6_hardware {
    volatile unsigned int id;   //0x000, Identification Register
    volatile unsigned int hwgeneral;    //0x004, General HW Parameters
    volatile unsigned int hwhost;   //0x008, Host HW Parameters
    int rsv0;                   //0x00c, not used in host core
    volatile unsigned int hwtxbuf;  //0x010, TX Buffer HW Parameters
    volatile unsigned int hwrxbuf;  //0x014, RX Buffer HW Parameters
    int rsv1[26];
    volatile unsigned int gptimer0ld;   //0x080, GP Timer0 Load Register
    volatile unsigned int gptimer0ctrl; //0x084, GP Timer0 Control Register
    volatile unsigned int gptimer1ld;   //0x088, GP Timer1 Load Register
    volatile unsigned int gptimer1ctrl; //0x08c, GP Timer1 control register
    volatile unsigned int sbuscfg;  //0x090, System Bus Configuration@mx28
    int rsv2[27];
    volatile unsigned int caplen_hciver;    //0x100, Capability Length Register
    volatile unsigned int hcsparams;    //0x104, Host Control Structural Parameters
    volatile unsigned int hccparams;    //0x108, Host Control Capability Parameters
    int rsv4[5];
    volatile unsigned int dciversion;   //0x0120, Device Interface Version Number
    volatile unsigned int dccparams;    //0x0124, Device Control Capability Parameters
    int rsv41[6];
    volatile unsigned int usbcmd;   //0x140, USB Command
    volatile unsigned int usbsts;   //0x144, USB Status
    volatile unsigned int usbintr;  //0x148, USB Interrupt Enable
    volatile unsigned int frindex;  //0x14c, USB Frame Index
    int rsv5;
#ifdef USB_DEVICE
    volatile unsigned int deviceaddr;   //0x0154, USB Device Address Register
    volatile unsigned int endpointlistaddr; //0x0158, Endpoint List Address Register
    int rsv6;
#else                           /* */
    volatile unsigned int periodiclistbase; //0x154, USB Controller Freame List Base Address
    volatile unsigned int asynclistaddr;    //0x158, USB Controller Next Asynch. Address
    volatile unsigned int ttctrl;   //0x015c, Embedded TT Asynchronous Buffer Status and Control Register
#endif                          /* */
    volatile unsigned int burstsize;    //0x160, Programmable Burst Size
    volatile unsigned int txfilltuning; //0x164, Host Transmit Pre-Buffer Packet Tuning
    int rsv7;
    volatile unsigned int icusb;    //0x0168, Inter-chip Control Register
    volatile unsigned int ulpiviewpoint;    //0x170, ULPI Viewport
    int rsv8;
    volatile unsigned int endptnak; //0x178, Endpoint NAK Register
    volatile unsigned int endptnaken;   //0x17c, Endpoint NAK Enable Regisgter
    int rsv81;
    volatile unsigned int portsc1;  //0x184, Port Port Status/Control1
    int rsv82[7];
    volatile unsigned int otgsc;    //0x1A4, OTG Status and Control Register
    volatile unsigned int usbmode;  //0x1A8, USB Device Mode
#ifdef USB_DEVICE               //only available for USB0, the OTG core
    volatile unsigned int endptsetupstat;   //0x1AC, Endpint Setup Status Register
    volatile unsigned int endptprime;   //0x1B0, Endpoint Initialization Register
    volatile unsigned int endptflush;   //0x1B4, Endpoint Fluah Register
    volatile unsigned int endptstat;    //0x1B8, Endpoint Status Register
    volatile unsigned int endptcomplete;    //0x1BC, Endpoint Complete Register
    volatile unsigned int endptctrl[8];   //0x1C0-0x1DC, Endpoint Control 0-7 Register
    int rsv9[8];
#else                           /* */
    int rsv9[21];
#endif                          /* */
} usb_mx6_hardware_t;

#define USBD_ADDR_MASK (0xFE000000) 

#endif //__USB_MX28_H
