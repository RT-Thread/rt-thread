/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @date
 *
 * @brief The file is a header file for USB Descriptors required for Mouse
 *        Application
 *****************************************************************************/

#ifndef _USB_DESCRIPTOR_H
#define _USB_DESCRIPTOR_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_class.h"
#ifdef _MC9S08_H
#include "flash_hcs.h"
#endif
#ifdef _MCF51_H
#include "flash.h"
#endif
#ifdef __MCF52xxx_H__
	#ifdef USED_EXTERNAL_FLASH
	#include "flash_NAND.h"
	#else
	#include "flash_cfv2.h"
	#endif
#endif
#include "usb_dfu.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define REMOTE_WAKEUP_SHIFT               (5)
#define REMOTE_WAKEUP_SUPPORT             (TRUE)

/* Various descriptor sizes */
#define DEVICE_DESCRIPTOR_SIZE            (18)
#define CONFIG_DESC_SIZE_RUNTIME          (52)
#define DEVICE_QUALIFIER_DESCRIPTOR_SIZE  (10)
#define REPORT_DESC_SIZE                  (52)
#define CONFIG_ONLY_DESC_SIZE             (9)
#define IFACE_ONLY_DESC_SIZE              (9)
#define HID_ONLY_DESC_SIZE                (9)
#define ENDP_ONLY_DESC_SIZE               (7)

/* HID buffer size */
#define HID_BUFFER_SIZE                   (8)
/* Max descriptors provided by the Application */
#define USB_MAX_STD_DESCRIPTORS               (8)
#define USB_MAX_CLASS_SPECIFIC_DESCRIPTORS    (2)
/* Max configuration supported by the Application */
#define USB_MAX_CONFIG_SUPPORTED          (1)

/* Max string descriptors supported by the Application */
#define USB_MAX_STRING_DESCRIPTORS        (4)

/* Max language codes supported by the USB */
#define USB_MAX_LANGUAGES_SUPPORTED       (1)


#define HID_DESC_ENDPOINT_COUNT (1)
#define HID_ENDPOINT (1)
#define HID_ENDPOINT_PACKET_SIZE (8)

#define MAX_BLOCK_SIZE  	     (8)

/* only control enpoint */
#define DFU_DESC_ENDPOINT_COUNT (0)              
#define FUNCTIONAL_DESC_SIZE              (9)

#define CONFIG_DESC_SIZE_DFU  (CONFIG_ONLY_DESC_SIZE + \
                                IFACE_ONLY_DESC_SIZE + \
                                FUNCTIONAL_DESC_SIZE + \
                                ENDP_ONLY_DESC_SIZE * DFU_DESC_ENDPOINT_COUNT)
/* string descriptors sizes */
#define USB_STR_DESC_SIZE         (2)
#define USB_STR_0_SIZE  		  (2)
#define USB_STR_1_SIZE           (56)
#define USB_STR_2_SIZE           (24)
#define USB_STR_3_SIZE           (20)
#define USB_STR_n_SIZE           (32)

/* descriptors codes */
#define USB_DEVICE_DESCRIPTOR     (1)
#define USB_CONFIG_DESCRIPTOR     (2)
#define USB_STRING_DESCRIPTOR     (3)
#define USB_IFACE_DESCRIPTOR      (4)
#define USB_ENDPOINT_DESCRIPTOR   (5)
#define USB_DEVQUAL_DESCRIPTOR    (6)
#define USB_HID_DESCRIPTOR        (0x21)
#define USB_REPORT_DESCRIPTOR     (0x22)

#define USB_MAX_SUPPORTED_INTERFACES     (1)
/* DFU functional codes */
#define USB_DFU_FUNCTIONAL_DESCRIPTOR     (0x21)


/* DFU functional codes */
#define DETACH               (1)
#define MANIFESTATION        (1)
#define BITCANUPLOAD         (1)
#define BITCANDOWNLOAD       (1)
/* DFU_EP is control enpoint*/
#define DFU_EP               0x00

/* DFU define request */
#define GETSTATUS_DATA_SIZE     (0x06)
#define SET_DNLOAD_DATA_SIZE    (0x08)
#define GET_UPLOAD_DATA_SIZE    (0x08)
#if(defined(_MC9S08JS16_H)||defined(_MC9S08JM16_H))
#define MAX_FIRMWARE_SIZE        (128)
#else
#define MAX_FIRMWARE_SIZE        (256)
#endif
#define MAX_BLOCKNUM              (MAX_FIRMWARE_SIZE/MAX_BLOCK_SIZE)

#define GETSTATE_DATA_SIZE      (0x01)
#define   RUNTIME_MODE             (1)
#define   DFU_MODE                 (2)
/******************************************************************************
 * Types
 *****************************************************************************/
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

typedef const struct _USB_ENDPOINTS
{
    /* Number of non control Endpoints */
    uint_8 count;
    /* Array of Endpoints Structures */
    USB_EP_STRUCT ep[HID_DESC_ENDPOINT_COUNT];
}USB_ENDPOINTS;

/******************************************************************************/
#define STORAGE_FIRMWARE FALSE

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

extern uint_8 USB_Class_DFU_Dnload(
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 wBlockNum,                   /* [IN] The BlockNum of firmware image */
        uint_8_ptr *data,                   /* [IN] Pointer to Data */
        USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
    );

extern uint_8 USB_Class_DFU_Upload (
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 BlockNum,                    /* [IN] Setup packet received */
        uint_8_ptr *data,                   /* [OUT] Pointer to Data */
        USB_PACKET_SIZE *size,               /* [OUT] Pointer to Size of Data */
        USB_PACKET_SIZE wLength             /* [IN] wLength */
    );

extern void USB_Class_DFU_Manifest (void);
extern void USB_Class_DFU_set_bwPoll_TimeOut(uint_32 app_timeout );
#endif
