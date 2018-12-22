/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file usb_descriptor.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file is a header file for USB Descriptors required for PHDC
 *        Application
 *
 *****************************************************************************/

#ifndef _USB_DESCRIPTOR_H
#define _USB_DESCRIPTOR_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_class.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define REMOTE_WAKEUP_SHIFT              (5)
#define REMOTE_WAKEUP_SUPPORT            (TRUE)

/* This macro enables/disables Meta Data Processing */
#define USB_METADATA_SUPPORTED 			(FALSE)
#define PHDC_BULK_OUT_EP_SIZE     		(64)
#define PHDC_BULK_IN_EP_SIZE      		(32)
#if USB_METADATA_SUPPORTED
    #if (PHDC_BULK_OUT_EP_SIZE < 32)
      #error Minimum Endpoint Size required is 32 bytes
    #endif

    #if (PHDC_BULK_IN_EP_SIZE < 32)
      #error Minimum Endpoint Size required is 32 bytes
    #endif
#endif

#if USB_METADATA_SUPPORTED
#define META_DATA_MSG_PRE_IMPLEMENTED    (TRUE)
#else
#define META_DATA_MSG_PRE_IMPLEMENTED    (FALSE)
#endif

/* Various descriptor sizes */
#define DEVICE_DESCRIPTOR_SIZE            (18)

#ifndef _MC9S08JS16_H
#if USB_METADATA_SUPPORTED
#define CONFIG_DESC_SIZE                  (72)
#else
#define CONFIG_DESC_SIZE                  (61)
#endif
#else
#if USB_METADATA_SUPPORTED
#define CONFIG_DESC_SIZE                  (61)
#else
#define CONFIG_DESC_SIZE                  (50)
#endif
#endif
#define DEVICE_QUALIFIER_DESCRIPTOR_SIZE  (10)
#define CONFIG_ONLY_DESC_SIZE             (9)
#define IFACE_ONLY_DESC_SIZE              (9)
#define ENDP_ONLY_DESC_SIZE               (7)
#define USB_PHDC_CLASSFUNCTION_DESC_SIZE  (4)
#define USB_QOS_DESC_SIZE                 (4)
#define USB_PHDC_FUNCTION_EXT_DESC_SIZE   (6)

#if USB_METADATA_SUPPORTED
#define USB_METADATA_BULK_OUT_DESC_SIZE   (4)
#define USB_METADATA_BULK_IN_DESC_SIZE    (7)
#ifndef _MC9S08JS16_H
#define USB_METADATA_INT_IN_DESC_SIZE     (2)
#endif
#endif

#ifndef _MC9S08JS16_H
#define PHDC_DESC_ENDPOINT_COUNT  (3)
#else
#define PHDC_DESC_ENDPOINT_COUNT  (2)
#endif
#define PHDC_BULK_OUT_EP          (1)
#define PHDC_BULK_IN_EP           (2)
#ifndef _MC9S08JS16_H
#define PHDC_INT_IN_EP            (3)
#endif

#ifndef _MC9S08JS16_H
#define PHDC_INT_IN_EP_SIZE       (8)
#endif

#define PHDC_BULK_IN_QOS          (0x08)
#define PHDC_BULK_OUT_QOS         (0x04)
#ifndef _MC9S08JS16_H
#define PHDC_INT_IN_QOS           (0x01)
#endif
/* PHDC buffer size */
#define PHDC_BUFFER_SIZE                   (8)
/* Max descriptors provided by the Application */
#define USB_MAX_STD_DESCRIPTORS           (7)
/* Max configuration supported by the Application */
#define USB_MAX_CONFIG_SUPPORTED          (1)

/* Max string descriptors supported by the Application */
#define USB_MAX_STRING_DESCRIPTORS        (3)

/* Max language codes supported by the USB */
#define USB_MAX_LANGUAGES_SUPPORTED       (1)

/* string descriptors sizes */
#define USB_STR_DESC_SIZE (2)
#define USB_STR_0_SIZE  (2)
#define USB_STR_1_SIZE  (56)
#define USB_STR_2_SIZE  (30)
#define USB_STR_n_SIZE  (32)

/* descriptors codes */
#define USB_DEVICE_DESCRIPTOR     (1)
#define USB_CONFIG_DESCRIPTOR     (2)
#define USB_STRING_DESCRIPTOR     (3)
#define USB_IFACE_DESCRIPTOR      (4)
#define USB_ENDPOINT_DESCRIPTOR   (5)
#define USB_DEVQUAL_DESCRIPTOR    (6)
#define USB_PHDC_CLASSFUNCTION_DESCRIPTOR (0x20)
#define USB_PHDC_QOS_DESCRIPTOR   (0x21)
#define PHDC_11073PHD_FUNCTION_DESCRIPTOR  (0x30)

#if USB_METADATA_SUPPORTED
#define PHDC_METADATA_DESCRIPTOR  (0x22)
#endif

#define USB_MAX_SUPPORTED_INTERFACES     (1)

/******************************************************************************
 * Types
 *****************************************************************************/
#ifndef __HIWARE__
#pragma pack(1)
#endif

typedef const struct _USB_LANGUAGE
{
    uint_16 const language_id;      /* Language ID */
    uint_8 const ** lang_desc;      /* Language Descriptor String */
    uint_8 const * lang_desc_size;  /* Language Descriptor Size */
} USB_LANGUAGE;

typedef const struct _USB_ALL_LANGUAGES
{
    /* Pointer to Supported Language String */
    uint_8 const *languages_supported_string;
    /* Size of Supported Language String */
    uint_8 const languages_supported_size;
    /* Array of Supported Languages */
    USB_LANGUAGE usb_language[USB_MAX_SUPPORTED_INTERFACES];
}USB_ALL_LANGUAGES;

typedef struct _usb_class_phdc_channel
{
    uint_8 channel_num;     /* endpoint num */
    uint_8 type;            /* type of the endpoint */
    uint_8 direction;       /* direction of the endpoint */
    USB_PACKET_SIZE size;   /* size of the endpoint buffer */
    uint_8 qos;             /* qos */
}USB_CLASS_PHDC_CHANNEL;


/* structure for the endpoints used */
typedef const struct _usb_class_phdc_channel_info
{
    /* Number of Non Control Endpoints */
    uint_8 count;
    /* Array of PHDC Channel Structures */
    USB_CLASS_PHDC_CHANNEL channel[PHDC_DESC_ENDPOINT_COUNT];
}USB_CLASS_PHDC_CHANNEL_INFO, *PTR_USB_CLASS_PHDC_CHANNEL_INFO;

#if defined(__CWCC__)
#pragma options align=reset
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#endif

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Desc_Get_Descriptor(
     uint_8 controller_ID,
     uint_8 type,
     uint_8 str_num,
     uint_16 index,
     uint_8_ptr *descriptor,
     USB_PACKET_SIZE *size);

extern uint_8 USB_Desc_Get_Interface(
    uint_8 controller_ID,
    uint_8 interface,
    uint_8_ptr alt_interface);


extern uint_8 USB_Desc_Set_Interface(
    uint_8 controller_ID,
    uint_8 interface,
    uint_8 alt_interface);

extern boolean USB_Desc_Valid_Configation(
    uint_8 controller_ID,
    uint_16 config_val);
extern boolean USB_Desc_Valid_Interface(
    uint_8 controller_ID,
    uint_8 interface);

extern boolean USB_Desc_Remote_Wakeup(uint_8 controller_ID);

extern void* USB_Desc_Get_Endpoints(uint_8 controller_ID);
#endif
