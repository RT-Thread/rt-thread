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
 * @brief The file contains USB descriptors for Video Application
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "user_config.h"
#include "usb_class.h"
#include "usb_descriptor.h"

#ifndef __NO_SETJMP
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>


#if (defined __MCF52xxx_H__)|| (defined __MK_xxx_H__) 
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST    const
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/* structure containing details of all the endpoints used by this device */
USB_DESC_CONST USB_ENDPOINTS usb_desc_ep = { VIDEO_DESC_ENDPOINT_COUNT, 
                                      {
                                      VIDEO_ENDPOINT,
                                      USB_ISOCHRONOUS_PIPE,
                                      USB_SEND,
                                      VIDEO_ENDPOINT_PACKET_SIZE
                                      },
};

/* *********************************************************************
* definition a struct of Input Terminal, Output Terminal or Feature Unit
************************************************************************ */                                  
                                                                            
 /* Struct of Input Terminal, Output Terminal or Feature Unit */                                 

USB_DESC_CONST USB_VIDEO_UNITS usb_video_unit = { VIDEO_UNIT_COUNT, 
                                 {
                                   {0x02,VC_INPUT_TERMINAL}, 
                                   {0x05,VC_PROCESSING_UNIT}, 
                                   {0x03,VC_OUTPUT_TERMINAL},
                                
                                  }
                              } ;
                              
uint_8 USB_DESC_CONST g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
  /* Device Descriptor */
   DEVICE_DESCRIPTOR_SIZE,               /* "Device Descriptor Size        */
   USB_DEVICE_DESCRIPTOR,                /* "Device" Type of descriptor    */
   0x00, 0x02,                           /*  BCD USB version               */
   0xEF,                                 /*  Miscellaneous Device Class    */
   0x02,                                 /*  Common Class  */
   0x01,                                 /*  Inteface Association Descriptor */
   CONTROL_MAX_PACKET_SIZE,              /*  Control endpoint packet size is 8 bytes */
   0xA2,0x15,                            /*  Vendor ID                     */
   0x0b,0x0E,                            /*  Product ID                    */
   0x00,0x03,                            /*  BCD Device version            */
   0x01,                                 /*  Manufacturer string index     */
   0x02,                                 /*  Product string index          */
   0x00,                                 /*  Serial number string index    */
   0x01                                  /*  Number of configurations      */    
};

uint_8 USB_DESC_CONST g_config_descriptor[CONFIG_DESC_SIZE] = 
{
   /* Configuration Descriptor */
   CONFIG_ONLY_DESC_SIZE,               /* Size of this desciptor in bytes */
   USB_CONFIG_DESCRIPTOR,               /* DEVICE descriptor */
   CONFIG_DESC_SIZE,0x00,               /* Length of total configuration block */
   0x02,                                /* This device has two interface */                            
   0x01,                                /* ID of this configuration */
   0x00,                                /* Unused */
   0x80,                               /* Bus-powered device, no remote wakeup */
   0xFA,                                /* 500mA maximum power consumption */

   /* Interface Association Descriptor */
   IAD_DESC_SIZE,                       /* Size of this descriptor */
   USB_IFACE_ASSOCIATION_DESCRIPTOR,    /* INTERFACE ASSOCIATION Descriptor */
   0x00,                                /* Interface number ofthe VideoControl 
                                        interface that is associated with this function */
   0x02,                                /* Number of contiguous Video interfaces
                                        that are associated with this function */
   CC_VIDEO,                            /* CC_VIDEO */
   0x03,                                /* SC_VIDEO_INTERFACE_COLLECTION */
   0x00,                                /* Not used */
   0x02,                                /* Index to string descriptor */
 
   /* Standard VC Interface Descriptor */
   IFACE_ONLY_DESC_SIZE,                /* Size of this descriptor */
   INTERFACE_DESC,                                /* INTERFACE descriptor type */
   0x00,                                /* Index of this interface */
   0x00,                                /* Index of this setting */
   0x01,                                /* 1 endpoint (interrupt endpoint) */
   CC_VIDEO,                            /* CC_VIDEO */
   0x01,                                /* SC_VIDEOCONTROL */
   0x00,                                /* Not used, PC_PROTOCOOL_UNDEFINED */
   0x02,                                /* Index of this string descriptor */
    
  /* Class-specific VC Inteface Descriptor */   
  VC_HEADER_ONLY_DESC_SIZE,                /* Size of this descriptor */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VC_HEADER,                            /* VC_HEADER subtype */
  0x00,0x01,                            /* Revision of class specification */
  0x32,0x00,                            /* Total size of class-specific descriptor */
  0x80,0x8D,0x5B,0x00,                  /* This device will provide timestamps and 
                                            and a device clock reference based on 6MHz clock */
  0x01,                                 /* Number of streaming interfaces */
  0x01,                                 /* VideoStreaming interface 1 belongs to
                                            this VideoControl interface */                                   
  
  /* Input Terminal Descriptor (Camera) */
  INPUT_TERMINAL_ONLY_DESC_SIZE,        /* Size of this descriptor */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VC_INPUT_TERMINAL,                    /* VC_INPUT_TERMINAL subtype */
  0x01,                                 /* ID of this input terminal */
  0x01,0x02,                            /* ITT_CAMERA type. This terminal is a 
                                        /* Camera terminal representing the CCD sensor */
  0x00,                                 /* No association */
  0x00,                                 /* Unused */
  0x00,0x00,                            /* No optical zoom supported */
  0x00,0x00,                            /* No optical zoom supported */
  0x00,0x00,                            /* No optical zoom supported */
  0x02,                                 /* The size of bmControls is 2 bytes */
  0x00,0x00,                            /* No controls are supported */
  
    /* Output Terminal Descriptor */
  OUTPUT_TERMINAL_ONLY_DESC_SIZE,       /* Size of this descriptor */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VC_OUTPUT_TERMINAL,                   /* VC_OUTPUT_TERMINAL */
  0x03,                                 /* ID of this descriptor */
  0x01,0x01,                            /* TT_STREAMING type.
                                           This terminal is a USB streaming terminal */
  0x00,                                 /* No association */
  0x02,                                 /* The input pin of this unit */
  0x00,                                 /* Unused */
    
  /* Processing Uint Descriptor */
  PROCESSING_UNIT_ONLY_DESC_SIZE,       /* Size of this descriptor */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VC_PROCESSING_UNIT,                   /* VC_PROCESSING_UNIT */
  0x02,                                 /* ID of this unit */
  0x01,                                 /* This input pin of this is connected to
                                        /*  unit with ID 0x04 */
  0x00,0x00,                            /* unused */
  0x02,                                 /* Size of the bmControls field */
  0x01,0x00,                            /* Brightness control supported */
  0x00,                                 /* Unused */
  
  /* Standard Interrupt Endpoint Descriptor */
  INTERRUPT_ENDPOINT_DESC_SIZE,         /* Size of this descriptor */
  USB_ENDPOINT_DESCRIPTOR,              /* ENDPOINT descriptor */
  0x81,                                 /* IN endpoint 1 */
  0x03,                                 /* Interrupt transfer type */
  0x08,0x00,                            /* 8 byte status packet */
  0x20,                                 /* Poll at lease every 32ms */
    
  /* Standard VS Interface Descriptor */
  IFACE_ONLY_DESC_SIZE,                 /* Size */
  INTERFACE_DESC,                       /* INTERFACE descriptor type */
  0x01,                                 /* Index of this interface */
  0x00,                                 /* Index of this alternate setting */
  0x00,                                 /* 0 endpoints - no bandwidth used */
  CC_VIDEO,                             /* CC_VIDEO */
  SC_VIDEOSTREAMING,                    /* SC_VIDEOSTREAMING */
  PC_PROTOCOL_UNDEFINED,                /* PC_PROTOCOL_UNDEFINED */
  0x00,                                 /* Unused */
  
  /* Class-specific VS Header Descriptor (Input) */
  0x0E,                                 /* Size */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VS_INPUT_HEADER,                      /* VS_INPUT_HEADER */
  0x01,                                 /* One format descriptor follows */
  0x3F,0x00,                            /* Total size of class-specific VideoStream
                                           interface descriptor */
  0x82,                                 /* Address of the isochronous endpoint
                                           used for video data */
  0x00,                                 /* No dynamic format change supported */
  0x03,                                 /* This Video Stream interface supplies
                                            terminal ID 3 (Output Terminal)*/
  0x00,                                 /* Device supports still image capture method 1 */
  0x00,                                 /* Hardware trigger supported for still image capture */
  0x00,                                 /* Hardware trigger should initiate a still image capture */
  0x01,                                 /* Size of the bmaControls field */
  0x00,                                 /* No VideoStreaming specific controls are supported */
  
  /* Class-specifc VS Format Descriptor */
  0x0B,                                 /* Size */
  CS_INTERFACE,                         /* CS_INTERFACE */
  0x06,                                 /* VS_FORMAT_MJEG */
  0x01,                                 /* First (and only) format descriptor */
  0x01,                                 /* One frame descriptor for this format follows */
  0x01,                                 /* Used fixed size samples */
  0x01,                                 /* Default frame index is 1 */
  0x00,                                 /* Non-interlaced stream - not required */
  0x00,                                 /* Non-interlaced stream - not required */
  0x00,                                 /* Non-interlaced stream */
  0x00,                                 /* No restrictions imposed on 
                                           the duplication of this video stream*/
  
  /* Class-specific VS Frame Descriptor */
  SPECIFIC_VS_FRAME_DESC_SIZE,          /* Size */
  CS_INTERFACE,                         /* CS_INTERFACE */
  VS_FRAME_MJPEG,                       /* VS_FRAME_MJPEG */
  0x01,                                 /* First (and only) frame descriptor */
  0x00,                                 /* Still images using capture method 1 are
                                        /*  supported at this frame setting.*/
                                        /*  D1: Fixed frame-rate*/
  0x40,0x01,                            /* Width of frame is 320 pixels */
  0xF0,0x00,                            /* Height of frame is 240 pixels */

  0x00,0x09,0x3D,0x00,                  /* Min bit rate in bits/s */
  0x00,0x09,0x3D,0x00,                  /* Max bit rate in bits/s */
    
  0x80,0x94,0x00,0x00,                  /* Max video or still frame size */
  
  0x2A,0x2C,0x0A,0x00,                  /* Default frame interval is 15fps */
  
  0x00,                                 /* Continuous frame interval*/
  0x2A,0x2C,0x0A,0x00,                  /* Min frame interval is 15fps */
  0x2A,0x2C,0x0A,0x00,                  /* Max frame interval is 15fps */
  0x00,0x00,0x00,0x00,                  /* No frame interval step supported */
  
  /* Standard VS Interface Descriptor */
  IFACE_ONLY_DESC_SIZE,                 /* Size */
  INTERFACE_DESC,                       /* INTERFACE descriptor type */
  0x01,                                 /* Index of this interface */
  0x01,                                 /* Index of this alternate setting */
  0x01,                                 /* 0 endpoints now banwidth used */
  CC_VIDEO,                             /* CC_VIDEO */
  SC_VIDEOSTREAMING,                    /* SC_VIDEOSTREAMING */
  PC_PROTOCOL_UNDEFINED,                /* PC_PROTOCOL_UNDEFINED */
  0x00,                                 /* Unused */
  
  /* Standard VS Isochronous Video Data Endpoint Descriptor */
  VIDEO_STREAMING_ENDP_DESC_SIZE,       /* Size */
  USB_ENDPOINT_DESCRIPTOR,              /* USB_ENDPOINT_DESCRIPTOR */
  0x82,                                 /* IN endpoint 2 */
  0x05,                                 /* Isochronous tranfer type */
  0xFE,0x01,                            /* Max packet size */
  0x01                                  /* One frame inteval */  
};

uint_8 USB_DESC_CONST USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =
                                    {sizeof(USB_STR_0),
                                     USB_STRING_DESCRIPTOR,
                                      0x09,
                                      0x04/*equiavlent to 0x0409*/
                                    };

uint_8 USB_DESC_CONST USB_STR_1[USB_STR_1_SIZE+USB_STR_DESC_SIZE]
                          = {  sizeof(USB_STR_1),
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

uint_8 USB_DESC_CONST USB_STR_2[USB_STR_2_SIZE+USB_STR_DESC_SIZE]
                          = {  sizeof(USB_STR_2),
                               USB_STRING_DESCRIPTOR,
                               'U',0,
                               'S',0,
                               'B',0,
                               ' ',0,
                               'V',0,
                               'I',0,
                               'D',0,
                               'E',0,
                               'O',0,
                               ' ',0,
                               'D',0,
                               'E',0,
                               'M',0,
                               'O',0,
                          };

uint_8 USB_DESC_CONST USB_STR_n[USB_STR_n_SIZE+USB_STR_DESC_SIZE]
                          = {  sizeof(USB_STR_n),
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
                                    {0,
                                     DEVICE_DESCRIPTOR_SIZE,
                                     CONFIG_DESC_SIZE,
                                     0, /* string */
                                     0, /* Interface */
                                     0, /* Endpoint */
                                     0, /* Device Qualifier */
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
                                                NULL, /* Device Qualifier */
                                                NULL, /* other speed config*/
                                                NULL
                                            };

uint_8 const g_string_desc_size[USB_MAX_STRING_DESCRIPTORS] =
                                    {sizeof(USB_STR_0),
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

USB_ALL_LANGUAGES g_languages = { USB_STR_0, sizeof(USB_STR_0),
                                  { (uint_16 const)0x0409,
                                   (const uint_8 **)g_string_descriptors,
                                      g_string_desc_size}
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
 *         USBERR_INVALID_REQ_TYPE             when Error
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
    /*Body*/
    UNUSED(controller_ID);
    switch(type)
    {        
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
                    }/*EndFor*/
                }/*EndFor*/

                /* set return val for descriptor and size */
                *descriptor = (uint_8_ptr)g_languages.usb_language[lang_id].
                                                    lang_desc[lang_index];
                *size = g_languages.usb_language[lang_id].
                                                    lang_desc_size[lang_index];
            }/*EndIf*/
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
        }/*Else*/
        else /* invalid descriptor */
        {
            return USBERR_INVALID_REQ_TYPE;
        }
        break;
    }/*EndSwitch*/
    return USB_OK;
}/* EndBody */

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
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *This function is called by the framework module to get the current interface
 *****************************************************************************/
uint_8 USB_Desc_Get_Interface(
      uint_8 controller_ID,     /* [IN] Controller ID */
      uint_8 interface,         /* [IN] Interface number */
      uint_8_ptr alt_interface  /* [OUT] Output alternate interface */
)
{
    /*Body*/
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get alternate interface*/
        *alt_interface = g_alternate_interface[interface];
        return USB_OK;
    }/*EndIf*/
    return USBERR_INVALID_REQ_TYPE;
}/*EndBody*/

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
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *This function is called by the framework module to set the interface
 *****************************************************************************/
uint_8 USB_Desc_Set_Interface(
      uint_8 controller_ID, /* [IN] Controller ID */
      uint_8 interface,     /* [IN] Interface number */
      uint_8 alt_interface  /* [IN] Input alternate interface */
)
{
    /*Body*/
    UNUSED (controller_ID);
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set alternate interface*/
        g_alternate_interface[interface] = alt_interface;
        return USB_OK;
    }/*EndIf*/

    return USBERR_INVALID_REQ_TYPE;
}/*EndBody*/

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

    /*Body*/    
    UNUSED (controller_ID);
    /* check with only supported val right now */
    while(loop_index < (USB_MAX_CONFIG_SUPPORTED+1))
    {
        if(config_val == g_valid_config_values[loop_index])
        {
            return TRUE;
        }/*EndIf*/
        loop_index++;
    }/*EndWhile*/
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
    
    /*Body*/
    UNUSED(controller_ID);
    /* check with only supported val right now */
    while(loop_index < USB_MAX_SUPPORTED_INTERFACES)
    {
        if(interface == g_alternate_interface[loop_index])
        {
            return TRUE;
        }/*EndIf*/
        loop_index++;
    }/*EndWhile*/
    return FALSE;
}/*EndBody*/
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
    UNUSED(controller_ID);
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
 * @name  USB_Desc_Get_Entities
 *
 * @brief The function returns with the list of all Input Terminal,
 * Output Terminal and Feature Unit
 *
 * @param controller_ID : Controller ID
 *
 * @return pointer to USB_VIDEO_UNITS
 *****************************************************************************
 * This function returns the information about all the Input Terminal,
 * Output Terminal and Feature Unit
 *****************************************************************************/ 
void* USB_Desc_Get_Video_Entities(
      uint_8 controller_ID      /* [IN] Controller ID */
)
{
    /*Body*/    
    UNUSED (controller_ID);
    return (void*)&usb_video_unit;
}/*EndBody*/

uint_8 g_cur_brightness[2] = {0x00,0x00};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Brightness
 *
 * @brief The function sets current brightness value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *Set current brightness value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
  UNUSED(size);
  
    g_cur_brightness[0]=**data;
    g_cur_brightness[1]=*(*data+1);
    
    return USB_OK;
}/*EndBody*/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Brightness
 *
 * @brief The function gets the current Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return current brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 2;
    *data = g_cur_brightness;
    
    return USB_OK;
}/*EndBody*/
uint_8 g_min_brightness[2] = {0xf0,0xff};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Min_Brightness
 *
 * @brief The function gets the minimum Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return minimum brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Min_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 2;
    *data = g_min_brightness;
    
    return USB_OK;
}/*EndBody*/
uint_8 g_max_brightness[2] = {0x10,0x00};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Max_Brightness
 *
 * @brief The function gets the maximum Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data             : Pointer to Data
 * @param size              : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return maximum brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Max_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 2;
    *data = g_max_brightness;
    
    return USB_OK;
}/*EndBody*/

uint_8 g_res_brightness[2] = {0x01,0x00};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Res_Brightness
 *
 * @brief The function gets the resolution Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return resolution brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Res_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 2;
    *data = g_res_brightness;
    
    return USB_OK;
}/*EndBody*/

uint_8 g_info_brightness[1] = {0x03};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Info_Brightness
 *
 * @brief The function gets the information Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return information brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Info_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 1;
    *data = g_info_brightness;
    
    return USB_OK;
}/*EndBody*/

uint_8 g_def_brightness[2] = {0x01,0x00};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Def_Brightness
 *
 * @brief The function gets the default Brightness value
 *
 * @param controller_ID : Controller ID
 * @param data             : Pointer to Data
 * @param size             : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return default brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Def_Brightness(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);

    *size = 2;
    *data = g_def_brightness;
    
    return USB_OK;
}/*EndBody*/

uint_8 g_cur_power_mode[1] = {0x00};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Power_Mode
 *
 * @brief The function sets current power mode value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *Set current power mode value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Power_Mode(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
  UNUSED(size);

    g_cur_power_mode[0]=**data;
    
    return USB_OK;
}/*EndBody*/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Power_Mode
 *
 * @brief The function gets the current power mode value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return current power mode value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Power_Mode(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*.Body*/
  UNUSED(controller_ID);

    *size = 1;
    *data = g_cur_power_mode;
    return USB_OK;
}/*EndBody*/

uint_8 g_info_power_mode[1] = {0x03};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Info_Power_Mode
 *
 * @brief The function gets the information power mode value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return information brightness value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Info_Power_Mode(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);

    *size = 1;
    *data = g_info_power_mode;
    return USB_OK;
}/*EndBody*/


uint_8 g_cur_error_code[1] = {0x07};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Error_Code
 *
 * @brief The function gets the current error code value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return current error code value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Error_Code(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);

    *size = 1;
    *data = g_cur_error_code;
    return USB_OK;
}/*EndBody*/

uint_8 g_info_error_code[1] = {0x01};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Info_Error_Code
 *
 * @brief The function gets the information error code value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return information error code value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Info_Error_Code(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);

    *size = 1;
    *data = g_info_error_code;
    return USB_OK;
}/*EndBody*/

uint_8 g_cur_video_probe[26] = {0x00,0x00,0x01,0x01,0x15,0x16,
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x58,0x02,0x00,0x5C,0x02,0x00,0x00
};

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Video_Probe
 *
 * @brief The function sets current probe value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *Set current probe value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Video_Probe(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
  uint_8 i;
  
  /*Body*/
   UNUSED(controller_ID);
   UNUSED(size);
  
    for(i=0;i<26;i++){
    g_cur_video_probe[i]=*(*data+i);
    }
    
    return USB_OK;
}/*EndBody*/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Video_Probe
 *
 * @brief The function gets the current probe value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return current probe value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Video_Probe(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=26;   
  *data=g_cur_video_probe;

    return USB_OK;
}/*EndBody*/

uint_8 g_len_video_probe[26] = {0x1a,0x00,0x01,0x01,0x15,0x16,
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x58,0x02,0x00,0x5C,0x02,0x00,0x00
};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Len_Video_Probe
 *
 * @brief The function gets the length probe value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return lengh probe value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Len_Video_Probe(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=26;   
  *data=g_len_video_probe;

    return USB_OK;
}/*EndBody*/

uint_8 g_info_video_probe[1] = {0x03};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Info_Video_Probe
 *
 * @brief The function gets the information probe value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return information probe value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Info_Video_Probe(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=1;   
  *data=g_info_video_probe;

    return USB_OK;
}/*EndBody*/

uint_8 g_cur_video_commit[26] = {0x00,0x00,0x01,0x01,0x15,0x16,
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x58,0x02,0x00,0x5C,0x02,0x00,0x00
};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Cur_Video_Commit
 *
 * @brief The function sets current commit value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *Set current commit value specified by the Host
 *****************************************************************************/
uint_8 USB_Desc_Set_Cur_Video_Commit(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
  uint_8 i;
  
  /*Body*/
  UNUSED(controller_ID);
  UNUSED(size);
  
    for(i=0;i<26;i++){
    g_cur_video_commit[i]=*(*data+i);
    }/*EndFor*/
    
    return USB_OK;
}/*EndBody*/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Cur_Video_Commit
 *
 * @brief The function gets the current commit value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return current commit value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Cur_Video_Commit(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=26;   
  *data=g_cur_video_commit;

    return USB_OK;
}/*EndBody*/

uint_8 g_len_video_commit[26] = {0x1a,0x00,0x01,0x01,0x15,0x16,
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x58,0x02,0x00,0x5C,0x02,0x00,0x00
};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Len_Video_Commit
 *
 * @brief The function gets the length Commit value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return length commit value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Len_Video_Commit(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=26;   
  *data=g_len_video_commit;

    return USB_OK;
}/*EndBody*/

uint_8 g_info_video_commit[1] = {0x03};
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Info_Video_Commit
 *
 * @brief The function gets the information commit value
 *
 * @param controller_ID : Controller ID
 * @param data          : Pointer to Data
 * @param size          : Pointer to Size of Data
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * Return information commit value to the Host
 *****************************************************************************/
uint_8 USB_Desc_Get_Info_Video_Commit(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
/*Body*/
  UNUSED(controller_ID);
    
  *size=1;   
  *data=g_info_video_commit;

    return USB_OK;
}/*EndBody*/

/* EOF */
