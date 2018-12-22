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
 * @date Jul-21-2010
 *
 * @brief The file is a header file for USB Descriptors required for virtual camera
 *        Application
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

#define IMPLEMENT_QUEUING                (TRUE)

#define INTERFACE_DESC                    (0x04)

/* Video Interface Class Code */
#define CC_VIDEO                          (0x0E)

/* Video Interface Subclass Codes */
#define SC_UNDEFINED                      (0x00)
#define SC_VIDEOCONTROL                   (0x01)
#define SC_VIDEOSTREAMING                 (0x02)
#define SC_VIDEO_INTERFACE_COLLECTION     (0x03)

/* Video Interface Protocol Codes */
#define PC_PROTOCOL_UNDEFINED             (0x00)

/* Video Class-Specific Descriptor Types */
#define CS_UNDEFINED                      (0x20)
#define CS_DEVICE                         (0x21)
#define CS_CONFIGURATION                  (0x22)
#define CS_STRING                         (0x23)
#define CS_INTERFACE                      (0x24)
#define CS_ENDPOINT                       (0x25)

/* Video Class-Specific VC Interface Descriptor Subtypes */
#define VC_DESCRIPTOR_UNDEFINED           (0x00)
#define VC_HEADER                         (0x01)
#define VC_INPUT_TERMINAL                 (0x02)
#define VC_OUTPUT_TERMINAL                (0x03)
#define VC_SECLECTOR_UNIT                 (0x04)
#define VC_PROCESSING_UNIT                (0x05)
#define VC_EXTENSION_UNIT                 (0x06)

/* Video Class-specific VS Interface Desriptor Subtypes */
#define VS_UNDEFINED                      (0x00)
#define VS_INPUT_HEADER                   (0x01)
#define VS_OUTPUT_HEADER                  (0x02)
#define VC_STILL_IMAGE_FRAME              (0x03)
#define VS_FORMAT_UNCOMPRESSED            (0x04)
#define VC_FRAME_UNCOMPRESSED             (0x05)
#define VC_FORMAT_MJPEG                   (0x06)
#define VC_FRAME_MJPEG                    (0x07)
#define VC_RESERVED1                      (0x08)
#define VC_RESERVED2                      (0x09)
#define VC_FORMAT_MPEG2TS                 (0x0A)
#define RESERVED3                         (0x0B)
#define VC_FORMAT_DV                      (0x0C)
#define VC_COLORFORMAT                    (0x0D)
#define RESERVED4                         (0x0E)
#define RESERVED5                         (0x0F)
#define VS_FORMAT_FRAME_BASED             (0x10)
#define VS_FRAME_FRAME_BASED              (0x11)
#define VS_FORMAT_STREAM_BASED            (0x12)

/* Video Class-Specific Endpoint Descriptor Subtypes */
#define EP_UNDEFINED                      (0x00)
#define EP_GENERAL                        (0x01)
#define EP_ENDPOINT                       (0x02)
#define EP_INTERRUPT                      (0x03)

/* Video Class-Specific Request Codes */
#define EP_UNDEFINED                      (0x00)
#define SET_CUR                           (0x01)
#define GET_CUR                           (0x81)
#define GET_MIN                           (0x82)
#define GET_MAX                           (0x83)
#define GET_RES                           (0x84)
#define GET_LEN                           (0x85)
#define GET_INFO                          (0x86)
#define GET_DEF                           (0x87)


/* VideoControl Interface Control Selector Codes */
#define VC_CONTROL_UNDEFINED              (0x00)
#define VC_VIDEO_POWER_MODE_CONTROL       (0x01)
#define VC_REQUEST_ERROR_CODE_CONTROL     (0x02)

/* Terminal Control Selector Codes */
#define TE_CONTROL_UNDEFINED              (0x00)

/* Selector Unit Control Selector Codes */
#define SU_CONTROL_UNDEFINED               (0x00)
#define SU_INPUT_SELECT_CONTROL            (0x01)

/* Camera Terminal Control Selector Codes */
#define CT_CONTROL_UNDEFINED                (0x00)
#define CT_SCANNING_MODE_CONTROL            (0x01)
#define CT_AE_MODE_CONTROL                  (0x02)
#define CT_AE_PRIORITY_CONTROL              (0x03)
#define CT_EXPOSURE_TIME_ABSOLUTE_CONTROL   (0x04)
#define CT_EXPOSURE_TIME_RELATIVE_CONTROL   (0x05)
#define CT_FOCUS_ABSOLUTE_CONTROL           (0x06)
#define CT_FOCUS_RELATIVE_CONTROL           (0x07)
#define CT_FOCUS_AUTO_CONTROL               (0x08)
#define CT_IRIS_ABSOLUTE_CONTROL            (0x09)
#define CT_IRIS_RELATIVE_CONTROL            (0x0A)
#define CT_ZOOM_ABSOLUTE_CONTROL            (0x0B)
#define CT_ZOOM_RELATIVE_CONTROL            (0x0C)
#define CT_PANTILT_ABSOLUTE_CONTROL         (0x0D)
#define CT_PANTILT_RELATIVE_CONTROL         (0x0E)
#define CT_ROLL_ABSOLUTE_CONTROL            (0x0F)
#define CT_ROLL_RELATIVE_CONTROL            (0x10)
#define CT_PRIVACY_CONTROL                  (0x11)

/* Processing Unit Control Selector Codes */
#define PU_CONTROL_UNDEFINED                      (0x00)
#define PU_BACKLIGHT_COMPENSATION_CONTROL         (0x01)
#define PU_BRIGHTNESS_CONTROL                     (0x02)
#define PU_CONTRACT_CONTROL                       (0x03)
#define PU_GAIN_CONTROL                           (0x04)
#define POWER_LINE_FREQUENCY_CONTROL              (0x05)
#define PU_HUE_CONTROL                            (0x06)
#define PU_SATURATION_CONTROL                     (0x07)
#define PU_SHARRNESS_CONTROL                      (0x08)
#define PU_GAMMA_CONTROL                          (0x09)
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL      (0x0A)
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL (0x0B)
#define PU_WHITE_BALANCE_COMPONENT_CONTROL        (0x0C)
#define PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL   (0x0D)
#define PU_DIGITAL_MULTIPLIER_CONTROL             (0x0E)
#define PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL       (0x0F)
#define PU_HUE_AUTO_CONTROL                       (0x10)
#define PU_ANALOG_VIDEO_STANDARD_CONTROL          (0x11)
#define PU_ANALOG_LOCK_STATUS_CONTROL             (0x12)

/* Extension Unit Control Selectors Codes */
#define XU_CONTROL_UNDEFINED                       (0x00)

/* VideoStreming Unit Control Selector Codes */
#define   VS_CONTROL_UNDEFINED                     (0x00)
#define   VS_PROBE_CONTROL                         (0x01)
#define   VS_COMMIT_CONTROL                        (0x02)
#define   VS_STILL_PROBE_CONTROL                   (0x03)
#define   VS_STILL_COMMIT_CONTROL                  (0x04)
#define   VS_STILL_IMAGE_TRIGGER_CONTROL           (0x05)
#define   VS_STREAM_ERROR_CODE_CONTROL             (0x06)
#define   VS_GENERATE_KEY_FRAME_CONTROL            (0x07)
#define   VS_UPDATE_FRAME_SEGMENT_CONTROL          (0x08)
#define   VS_SYNCH_DELAY_CONTROL                   (0x09)

/* descriptors codes */
#define USB_DEVICE_DESCRIPTOR     (1)
#define USB_CONFIG_DESCRIPTOR     (2)
#define USB_STRING_DESCRIPTOR     (3)
#define USB_IFACE_DESCRIPTOR      (4)
#define USB_ENDPOINT_DESCRIPTOR   (5)
#define USB_DEVQUAL_DESCRIPTOR    (6)

#define ITT_CAMERA (0x0201)

#define VS_FRAME_MJPEG            (0x07)

#define USB_IFACE_ASSOCIATION_DESCRIPTOR  (0x0B)

/* string descriptors sizes */
#define USB_STR_DESC_SIZE (2)
#define USB_STR_0_SIZE  (2)
#define USB_STR_1_SIZE  (56)
#define USB_STR_2_SIZE  (28)
#define USB_STR_n_SIZE  (32)


/* Various descriptor sizes */
#define DEVICE_DESCRIPTOR_SIZE            (0x12)
#define CONFIG_DESC_SIZE                  (0xAB)
#define CONFIG_ONLY_DESC_SIZE             (9)
#define IFACE_ONLY_DESC_SIZE              (9)

#define VC_HEADER_ONLY_DESC_SIZE          (0x0D)
#define INPUT_TERMINAL_ONLY_DESC_SIZE     (0x11)
#define OUTPUT_TERMINAL_ONLY_DESC_SIZE    (0x09)
#define PROCESSING_UNIT_ONLY_DESC_SIZE    (0x0B)
#define INTERRUPT_ENDPOINT_DESC_SIZE      (0x07)
#define VIDEO_STREAMING_ENDP_DESC_SIZE    (0x07)

#define SPECIFIC_VS_FRAME_DESC_SIZE       (0x26)
#define IAD_DESC_SIZE                     (0x08)

/* Max descriptors provided by the Application */
#define USB_MAX_STD_DESCRIPTORS               (8)
#define USB_MAX_CLASS_SPECIFIC_DESCRIPTORS    (2)
/* Max configuration supported by the Application */
#define USB_MAX_CONFIG_SUPPORTED          (1)

/* Max string descriptors supported by the Application */
#define USB_MAX_STRING_DESCRIPTORS        (4)

/* Max language codes supported by the USB */
#define USB_MAX_LANGUAGES_SUPPORTED       (1)

#define VIDEO_UNIT_COUNT                  (3)
#define VIDEO_DESC_ENDPOINT_COUNT         (1)
#define VIDEO_ENDPOINT                    (2)


#define VIDEO_ENDPOINT_PACKET_SIZE (510)

#define USB_AUDIO_DESCRIPTOR      (0x25)
#define USB_REPORT_DESCRIPTOR     (0x22)

#define USB_MAX_SUPPORTED_INTERFACES     (2)

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
    USB_EP_STRUCT ep[VIDEO_DESC_ENDPOINT_COUNT];
}USB_ENDPOINTS;

typedef struct _USB_VIDEO_UT_STRUCT
{
  uint_8          unit_id;      /* endpoint number         */
  uint_8          type;        /* type of endpoint        */
}USB_UT_STRUCT, *USB_UT_STRUCT_PTR;

typedef const struct _USB_VIDEO_UNITS 
{
   /* Number of entities of this application */
   uint_8         count;
   /* Array of entities of this application */
   USB_UT_STRUCT  et[VIDEO_UNIT_COUNT];
}USB_VIDEO_UNITS;

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

extern void* USB_Desc_Get_Video_Entities(uint_8 controller_ID);

extern uint_8 USB_Desc_Set_Cur_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Cur_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Min_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);


extern uint_8 USB_Desc_Get_Max_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);


extern uint_8 USB_Desc_Get_Res_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

#if 0
extern uint_8 USB_Desc_Get_Len_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
#endif

extern uint_8 USB_Desc_Get_Info_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);


extern uint_8 USB_Desc_Get_Def_Brightness(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Set_Cur_Power_Mode(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Cur_Power_Mode(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Info_Power_Mode(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Cur_Error_Code(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Info_Error_Code(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Set_Cur_Video_Probe(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Cur_Video_Probe(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Len_Video_Probe(
    uint_8 controller_ID,              
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);

extern uint_8 USB_Desc_Get_Info_Video_Probe(
    uint_8 controller_ID,              
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);

extern uint_8 USB_Desc_Set_Cur_Video_Commit(
    uint_8 controller_ID,              
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);

extern uint_8 USB_Desc_Get_Cur_Video_Commit(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Len_Video_Commit(
    uint_8 controller_ID,               
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

extern uint_8 USB_Desc_Get_Info_Video_Commit(
    uint_8 controller_ID,               
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size               
);

#endif