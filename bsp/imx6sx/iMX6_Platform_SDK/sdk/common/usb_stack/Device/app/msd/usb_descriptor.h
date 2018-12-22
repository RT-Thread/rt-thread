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
 * @date May-08-2009
 *
 * @brief The file contains USB stack class layer api header function.
 *
 *****************************************************************************/

#ifndef _USB_DESCRIPTOR_H
#define _USB_DESCRIPTOR_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"
#include "usb_framework.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/ \
#define BCD_USB_VERSION                  (0x0200)

#define REMOTE_WAKEUP_SUPPORT            (0)/*1: TRUE, 0: FALSE*/
#define REMOTE_WAKEUP_SHIFT              (5)

#define IMPLEMENT_QUEUING                (1)/*1:TRUE; 0:FALSE*/

/* Implementation Specific Macros */
#define MSC_DESC_ENDPOINT_COUNT         (2)

#define BULK_IN_ENDPOINT             (1)
#if HIGH_SPEED_DEVICE
#define BULK_IN_ENDP_PACKET_SIZE    (512)/* max supported is 64 and 512 for HS*/
#else
#define BULK_IN_ENDP_PACKET_SIZE     (32)/* max supported is 64 for FS and 512 for HS*/
#endif
#define BULK_OUT_ENDPOINT            (2)
#if HIGH_SPEED_DEVICE
#define BULK_OUT_ENDP_PACKET_SIZE    (512)/* max supported is 64 and 512 for HS*/
#else
#define BULK_OUT_ENDP_PACKET_SIZE    (32)/* max supported is 64 and 512 for HS*/
#endif

#if (BULK_OUT_ENDP_PACKET_SIZE < 32)
	#error "BULK_OUT_ENDP_PACKET_SIZE cannot be less than 32"
#endif
/* Various descriptor sizes */ 
#define DEVICE_DESCRIPTOR_SIZE            (18)
#define CONFIG_ONLY_DESC_SIZE             (9)
#define IFACE_ONLY_DESC_SIZE              (9)
#define ENDP_ONLY_DESC_SIZE               (7)

#define CONFIG_DESC_SIZE       (CONFIG_ONLY_DESC_SIZE + \
                                IFACE_ONLY_DESC_SIZE + \
                                ENDP_ONLY_DESC_SIZE * MSC_DESC_ENDPOINT_COUNT)

#if HIGH_SPEED_DEVICE
	#define DEVICE_QUALIFIER_DESCRIPTOR_SIZE    (10)
	#define OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE  (CONFIG_DESC_SIZE)	
#endif


/* Max descriptors provided by the Application */
#define USB_MAX_STD_DESCRIPTORS           (7) 

/* Max configuration supported by the Application */
#define USB_MAX_CONFIG_SUPPORTED          (1)

/* Max string descriptors supported by the Application */
#define USB_MAX_STRING_DESCRIPTORS        (4)

/* Max language codes supported by the USB */
#define USB_MAX_LANGUAGES_SUPPORTED       (1)
 
/* string descriptors sizes */
#define USB_STR_DESC_SIZE (2)
#define USB_STR_0_SIZE    (2)
#define USB_STR_1_SIZE    (56)

#if RAM_DISK_APP
  #define USB_STR_2_SIZE    (30)
#elif SD_CARD_APP
  #define USB_STR_2_SIZE    (34)
#endif

#define USB_STR_3_SIZE    (32)
#define USB_STR_n_SIZE    (32)

/* descriptors codes */
#define USB_DEVICE_DESCRIPTOR     (1)
#define USB_CONFIG_DESCRIPTOR     (2)
#define USB_STRING_DESCRIPTOR     (3)
#define USB_IFACE_DESCRIPTOR      (4)
#define USB_ENDPOINT_DESCRIPTOR   (5)

#define USB_MAX_SUPPORTED_INTERFACES     (1)

#if HIGH_SPEED_DEVICE
	#define USB_DEVQUAL_DESCRIPTOR      (6)
	#define USB_OTHER_SPEED_DESCRIPTOR  (7)
#endif

#define DEVICE_DESC_DEVICE_CLASS             (0x00)
#define DEVICE_DESC_DEVICE_SUBCLASS          (0x00)
#define DEVICE_DESC_DEVICE_PROTOCOL          (0x00)
#define DEVICE_DESC_NUM_CONFIG_SUPPOTED      (0x01)
#define CONFIG_DESC_NUM_INTERFACES_SUPPOTED  (0x01)
#define CONFIG_DESC_CURRENT_DRAWN            (0x32)

/* mass storage specific macros */
#define MASS_STORAGE_CLASS           (0x08)
#define SCSI_TRANSPARENT_COMMAND_SET (0x06)
#define BULK_ONLY_PROTOCOL           (0x50)
#define PERIPHERAL_DEVICE_TYPE       (0x00)
        			/* Direct Access Block Device : Magnetic and Flash Drives*/
#define PERIPHERAL_QUALIFIER_SHIFT   (5)
#define PERIPHERAL_QUALIFIER         (0)
#define SPC_VERSION                  (4)/*SPC3 is 5; SPC2 is 4*/
#define REMOVABLE_MEDIUM_BIT         (1) 
#define REMOVABLE_MEDIUM_BIT_SHIFT   (7)
#define ADDITIONAL_LENGTH            (0x20)
                         /*set to 0x20H if returning 36 bytes of inquiry data*/

#define SUPPORT_DISK_LOCKING_MECHANISM  (0) /*1: TRUE; 0:FALSE*/
#define IMPLEMENTING_DISK_DRIVE         (0) /*1: TRUE; 0:FALSE*/

/******************************************************************************
 * Types
 *****************************************************************************/ 
#ifndef __HIWARE__
#pragma pack(1)
#endif
 
typedef const struct _USB_LANGUAGE 
{
    uint_16 const language_id;
    uint_8 const ** lang_desc;
    uint_8 const * lang_desc_size;    
} USB_LANGUAGE;
 
typedef struct _USB_ALL_LANGUAGES 
{
    uint_8 const *languages_supported_string;
    uint_8 const languages_supported_size;
    USB_LANGUAGE usb_language[USB_MAX_SUPPORTED_INTERFACES];
       
}USB_ALL_LANGUAGES;

typedef const struct _USB_ENDPOINTS
{
    uint_8 count;
    USB_EP_STRUCT ep[MSC_DESC_ENDPOINT_COUNT];
}USB_ENDPOINTS;

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
     uint_32 *size);
      
extern uint_8 USB_Desc_Get_Interface(
                              uint_8 controller_ID, 
                              uint_8 interface, 
                              uint_8_ptr alt_interface);


extern uint_8 USB_Desc_Set_Interface(
                              uint_8 controller_ID, 
                              uint_8 interface, 
                              uint_8 alt_interface);

extern boolean USB_Desc_Valid_Configation(uint_8 controller_ID, 
                                          uint_16 config_val); 

extern boolean USB_Desc_Remote_Wakeup(uint_8 controller_ID); 

extern USB_ENDPOINTS *USB_Desc_Get_Endpoints(uint_8 controller_ID);

#endif

/* EOF */