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
 * @date 
 *
 * @brief The file is a header file for USB Descriptors required for speaker
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
#define REMOTE_WAKEUP_SHIFT                         (5)
#define REMOTE_WAKEUP_SUPPORT                       (TRUE)

#define IMPLEMENT_QUEUING                           (TRUE)

/* Various descriptor sizes */
#define DEVICE_DESCRIPTOR_SIZE                      (18)
#if AUDIO_CLASS_2_0 == 0
#define CONFIG_DESC_SIZE                            (152)//(0x6D + 9)
#else
//#define CONFIG_DESC_SIZE                          (152) /* with 2 channels */
#define CONFIG_DESC_SIZE                            (148) /* with 1 channel */
#endif /* AUDIO_CLASS_2_0 */
#define DEVICE_QUALIFIER_DESCRIPTOR_SIZE            (10)
#define REPORT_DESC_SIZE                            (50)
#define CONFIG_ONLY_DESC_SIZE                       (9)
#define IFACE_ONLY_DESC_SIZE                        (9)
#define AUDIO_ONLY_DESC_SIZE                        (9)
#define ENDP_ONLY_DESC_SIZE                         (9)
#define HEADER_ONLY_DESC_SIZE                       (9)
#define INPUT_TERMINAL_ONLY_DESC_SIZE               (12)
#define OUTPUT_TERMINAL_ONLY_DESC_SIZE              (9)
#define FEATURE_UNIT_ONLY_DESC_SIZE                 (9)
#define AUDIO_STREAMING_IFACE_DESC_SIZE             (7)
#define AUDIO_STREAMING_ENDP_DESC_SIZE              (7)
#define AUDIO_INTERFACE_DESC_TYPE_I_SIZE            (11)

#define USB_DEVICE_CLASS_AUDIO                      (0x01)
#define USB_SUBCLASS_AUDIOCONTROL                   (0x01)
#define USB_SUBCLASS_AUDIOSTREAM                    (0x02)

#define AUDIO_INTERFACE_DESCRIPTOR_TYPE             (0x24)

#define AUDIO_CONTROL_HEADER                        (0x01)
#define AUDIO_CONTROL_INPUT_TERMINAL                (0x02)
#define AUDIO_CONTROL_OUTPUT_TERMINAL               (0x03)
#define AUDIO_CONTROL_MIXER_UNIT                    (0x04)
#define AUDIO_CONTROL_SELECTOR_UNIT                 (0x05)
#define AUDIO_CONTROL_FEATURE_UNIT                  (0x06)
#define AUDIO_CONTROL_EFFECT_UNIT                   (0x07)
#define AUDIO_CONTROL_PROCESSING_UNIT               (0x08)
#define AUDIO_CONTROL_EXTENSION_UNIT                (0x09)

#define AUDIO_STREAMING_GENERAL                     (0x01)
#define AUDIO_STREAMING_FORMAT_TYPE                 (0x02)
#define AUDIO_FORMAT_TYPE_I                         (0x01)
#define AUDIO_ENDPOINT_GENERAL                      (0x01)

/* AUDIO Class 2.0 */
#if AUDIO_CLASS_2_0
#define AUDIO_CONTROL_CLOCK_SOURCE                  (0x0A)
#define AUDIO_CONTROL_CLOCK_SELECTOR                (0x0B)
#define AUDIO_CONTROL_CLOCK_MULTIPLIER              (0x0C)
#define AUDIO_CONTROL_SAMPLE_RATE_CONVERTER         (0x0D)
#endif /* AUDIO_CLASS_2_0 */

#define AUDIO_BUFFER_SIZE                           (8)

/* Audio controls at Feature Unit descriptor level */
#define AUDIO_MUTE_CONTROL                          (0x01)
#define AUDIO_VOLUME_CONTROL                        (0x02)
#define AUDIO_BASS_CONTROL                          (0x04)
#define AUDIO_MID_CONTROL                           (0x08)
#define AUDIO_TREBLE_CONTROL                        (0x10)
#define AUDIO_GRAPHIC_EQ_CONTROL                    (0x20)
#define AUDIO_AUTOMATIC_GAIN_CONTROL                (0x40)
#define AUDIO_DELAY_CONTROL                         (0x80)


/* Max descriptors provided by the Application */
#define USB_MAX_STD_DESCRIPTORS                     (8)
#define USB_MAX_CLASS_SPECIFIC_DESCRIPTORS          (2)
/* Max configuration supported by the Application */
#define USB_MAX_CONFIG_SUPPORTED                    (1)

/* Max string descriptors supported by the Application */
#define USB_MAX_STRING_DESCRIPTORS                  (4)
    
/* Max language codes supported by the USB */
#define USB_MAX_LANGUAGES_SUPPORTED                 (1)


#if AUDIO_CLASS_2_0
#define AUDIO_UNIT_COUNT                            (4)
#else
#define AUDIO_UNIT_COUNT                            (3)
#endif /* AUDIO_CLASS_2_0 */
#define AUDIO_DESC_ENDPOINT_COUNT                   (2)
#define AUDIO_ENDPOINT                              (1)
#define AUDIO_FEEDBACK_ENDPOINT                     (2)


#define AUDIO_ENDPOINT_PACKET_SIZE                  (8)
#define AUDIO_FEEDBACK_ENDPOINT_PACKET_SIZE         (3)

/* string descriptors sizes */
#define USB_STR_DESC_SIZE                           (2)
#define USB_STR_0_SIZE                              (2)
#define USB_STR_1_SIZE                              (56)
#define USB_STR_2_SIZE                              (28)
#define USB_STR_n_SIZE                              (32)

/* descriptors codes */
#define USB_DEVICE_DESCRIPTOR                       (0x01)
#define USB_CONFIG_DESCRIPTOR                       (0x02)
#define USB_STRING_DESCRIPTOR                       (0x03)
#define USB_IFACE_DESCRIPTOR                        (0x04)
#define USB_ENDPOINT_DESCRIPTOR                     (0x05)
#define USB_DEVQUAL_DESCRIPTOR                      (0x06)
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR    (0x07)
#define USB_INTERFACE_POWER_DESCRIPTOR              (0x08)
#define USB_OTG_DESCRIPTOR                          (0x09)
#define USB_DEBUG_DESCRIPTOR                        (0x0A)
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR        (0x0B)

#define USB_AUDIO_DESCRIPTOR                        (0x25)
#define USB_REPORT_DESCRIPTOR                       (0x22)

#define USB_MAX_SUPPORTED_INTERFACES                (2)

#define PCM_FORMAT                                  (0x02)
#define SUB_FRAME_SIZE                              (0x01)
#define BIT_RESOLUTION                              (0x08)
#define NB_CHANNELS                                 (0x01)

#define EP01_IN                                     (0x81)
#define EP01_OUT                                    (0x01)
#define EP02_IN                                     (0x82)
#define EP02_OUT                                    (0x02)
#define EP03_IN                                     (0x83)
#define EP03_OUT                                    (0x03)

/* 
 * Interface delay: number of frames approximately needed by device to process 
 * a packet */
#define INTERFACE_DELAY                             (0x01)

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
    USB_EP_STRUCT ep[AUDIO_DESC_ENDPOINT_COUNT];
}USB_ENDPOINTS;

typedef struct _USB_AUDIO_UT_STRUCT
{
  uint_8          unit_id;      /* endpoint number         */
  uint_8          type;        /* type of endpoint        */
}USB_UT_STRUCT, *USB_UT_STRUCT_PTR;

typedef const struct _USB_AUDIO_UNITS 
{
   /* Number of entities of this application */
   uint_8         count;
   /* Array of entities of this application */
   USB_UT_STRUCT  et[AUDIO_UNIT_COUNT];
}USB_AUDIO_UNITS;

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
extern void* USB_Desc_Get_Audio_Entities(uint_8 controller_ID);

extern uint_8 USB_Desc_Set_Copy_Protect(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Copy_Protect(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Mute(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Mute(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Volume(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Bass(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Mid(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Treble(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Graphic_Equalizer(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Automatic_Gain(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Automatic_Gain(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Delay(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Bass_Boost(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Bass_Boost(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Loudness(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Loudness(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Min_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Max_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Res_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Min_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Max_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Res_Sampling_Frequency(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Cur_Pitch(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Cur_Pitch(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Set_Mem_Endpoint(
    uint_8 controller_ID, 
    uint_16 offset,              
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
extern uint_8 USB_Desc_Get_Mem_Endpoint(
    uint_8 controller_ID,               
    uint_16 offset,
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
#endif
