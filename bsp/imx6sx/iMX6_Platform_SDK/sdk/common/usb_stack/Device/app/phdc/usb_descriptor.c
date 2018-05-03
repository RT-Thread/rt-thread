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
 * @date May-28-2009
 *
 * @brief The file contains USB descriptors for PHDC Application
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "derivative.h"
#include "types.h"
#include "usb_class.h"
#include "usb_descriptor.h"

#if (defined __MCF52xxx_H__) || (defined __MK_xxx_H__)
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST	const
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
/* structure containing details of all the endpoints used by this device */
const USB_CLASS_PHDC_CHANNEL_INFO usb_desc_ep = { PHDC_DESC_ENDPOINT_COUNT,
                                      {PHDC_BULK_OUT_EP,
                                       USB_BULK_PIPE,
                                       USB_RECV,
                                       PHDC_BULK_OUT_EP_SIZE,
                                       PHDC_BULK_OUT_QOS,

                                       PHDC_BULK_IN_EP,
                                       USB_BULK_PIPE,
                                       USB_SEND,
                                       PHDC_BULK_IN_EP_SIZE,
                                       PHDC_BULK_IN_QOS,
 #ifndef _MC9S08JS16_H
                                       PHDC_INT_IN_EP,
                                       USB_INTERRUPT_PIPE,
                                       USB_SEND,
                                       PHDC_INT_IN_EP_SIZE,
                                       PHDC_INT_IN_QOS,
#endif
                                      }
                                  };


uint_8 USB_DESC_CONST g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    DEVICE_DESCRIPTOR_SIZE,               /* "Device Dexcriptor Size        */
    USB_DEVICE_DESCRIPTOR,                /* "Device" Type of descriptor    */
    0x00, 0x02,                           /*  BCD USB version               */
    0x00,                                 /*  Device Class is indicated in
                                             the interface descriptors      */
    0x00,                                 /*  Device Subclass is indicated
                                             in the interface descriptors   */
    0x00,                                 /*  Device Protocol               */
    CONTROL_MAX_PACKET_SIZE,              /*  Max Packet size               */
    0xA2,0x15,                            /*  Vendor ID                     */
    0x00,0x04,                            /*  Product ID                    */
      0x02,0x00,                          /*  BCD Device version            */
    0x01,                                 /*  Manufacturer string index     */
    0x01,                                 /*  Product string index          */
    0x00,                                 /*  Serial number string index    */
    0x01                                  /*  Number of configurations      */
};

uint_8 USB_DESC_CONST g_config_descriptor[CONFIG_DESC_SIZE] =
{
    CONFIG_ONLY_DESC_SIZE,  /* Configuration Descriptor Size - always 9 bytes*/
    USB_CONFIG_DESCRIPTOR,  /* "Configuration" type of descriptor */
    CONFIG_DESC_SIZE, 0x00, /*  Total length of the Configuration descriptor */
    1,                      /*  NumInterfaces */
    1,                      /*  Configuration Value */
    0,                      /*  Configuration Description String Index*/
    BUS_POWERED|SELF_POWERED|(REMOTE_WAKEUP_SUPPORT<<REMOTE_WAKEUP_SHIFT),
             /*  Attributes.support RemoteWakeup and self power */
    0x32,                   /*  Current draw from bus */

    /* Interface Descriptor */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x00,
    0x00,
    PHDC_DESC_ENDPOINT_COUNT,              /*  no. of endpoints-- one
                                              BULK OUT, one BULK IN,
                                              one INTERRUPT IN EP        */
    0x0F,                                  /*  class code for PHDC        */
    0x00,                                  /*  subclass code -- does
                                              not assign a subclass      */
    0x00,                                  /*  protocol code -- does
                                              not assign a protocol      */
    0x00,

    /* PHDC class function descriptor */
    USB_PHDC_CLASSFUNCTION_DESC_SIZE,
    USB_PHDC_CLASSFUNCTION_DESCRIPTOR,     /*  descriptor type            */
    0x02,                                  /*  data and messaging formats
                                              not defined by vendor
                                              DATA FORMAT --
                                              PHDC_11073_20601           */
    0x00|(META_DATA_MSG_PRE_IMPLEMENTED),

    /*PHDC function extension descriptor */
    USB_PHDC_FUNCTION_EXT_DESC_SIZE,
    
    PHDC_11073PHD_FUNCTION_DESCRIPTOR,
    0x00,
    0x01,
    0x34, 0x12,



    /*Endpoint descriptor-- BULK IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_BULK_IN_EP,
    USB_BULK_PIPE,
    PHDC_BULK_IN_EP_SIZE, 0x00,
    0x00,                                  /*  polling interval */

    /* PHDC QoS descriptor for BULK IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    0x01,                                  /* qos encoding version */
    PHDC_BULK_IN_QOS,                      /*  latency/reliability bin */

#if USB_METADATA_SUPPORTED
    /* PHDC Meta Data descriptor for BULK IN */
    USB_METADATA_BULK_IN_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    0xAB,      /* opaque meta data */
    0xCD,
    0xEF,
    0x01,
    0x02,
#endif
    /*Endpoint descriptor-- BULK OUT */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_RECV << 7) | PHDC_BULK_OUT_EP,
    USB_BULK_PIPE,
    PHDC_BULK_OUT_EP_SIZE, 0x00,
    0x00,                                  /*  polling interval */

    /* PHDC QoS descriptor for BULK OUT */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    0x01,                                  /* qos encoding version */
    PHDC_BULK_OUT_QOS,                     /* latency/reliability bin */

#if USB_METADATA_SUPPORTED
    /* PHDC Meta Data descriptor for BULK OUT */
    USB_METADATA_BULK_OUT_DESC_SIZE,
    PHDC_METADATA_DESCRIPTOR,
    0xCC,    /* opaque meta data */
    0xDD,
#endif

#ifndef _MC9S08JS16_H
    /*Endpoint descriptor-- INTERRUPT IN */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    (USB_SEND << 7) | PHDC_INT_IN_EP,
    USB_INTERRUPT_PIPE,
    PHDC_INT_IN_EP_SIZE, 0x00,
#if HIGH_SPEED_DEVICE
    0x04,
#else
    0xF0,                                  /*  polling interval */
#endif

     /* PHDC QoS descriptor for INTERRUPT IN */
    USB_QOS_DESC_SIZE,
    USB_PHDC_QOS_DESCRIPTOR,
    0x01,                                      /* qos encoding version */
    PHDC_INT_IN_QOS                            /*  latency/reliability bin */
#endif
};

uint_8 USB_DESC_CONST USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =
                                    {sizeof(USB_STR_0),
                                     USB_STRING_DESCRIPTOR,
                                      0x09,
                                      0x04
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
                               ' ',0,
                               ' ',0,
							#ifdef __MK_xxx_H__
							   'M',0,
							   'K',0,                               
							#elif (defined __MCF52xxx_H__)
							   'C',0,
							   'F',0,
							#elif (defined MCU_mcf51jf128)
							   'J',0,
							   'F',0,  	   
							#else     
							   'J',0,
							   'M',0,
							#endif               
                               ' ',0,
                               'P',0,
                               'H',0,
                               'D',0,
                               'C',0,
                               ' ',0,
                               'D',0,
                               'E',0,
                               'M',0,
                               'O',0,
                               ' ',0
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
                                     0 /* other speed config */
                                    };

uint_8_ptr const g_std_descriptors[USB_MAX_STD_DESCRIPTORS+1] = {
                                                NULL,
                                                (uint_8_ptr)g_device_descriptor,
                                                (uint_8_ptr)g_config_descriptor,
                                                NULL, /* string */
                                                NULL, /* Interface */
                                                NULL, /* Endpoint */
                                                NULL, /* Device Qualifier */
                                                NULL, /* other speed config*/
                                                             };

uint_8 const g_string_desc_size[USB_MAX_STRING_DESCRIPTORS+1] =
                                    {sizeof(USB_STR_0),
                                     sizeof(USB_STR_1),
                                     sizeof(USB_STR_2),
                                     sizeof(USB_STR_n)
                                    };

uint_8_ptr const g_string_descriptors[USB_MAX_STRING_DESCRIPTORS+1] =
										  {
											  (uint_8_ptr const) USB_STR_0,
											  (uint_8_ptr const) USB_STR_1,
											  (uint_8_ptr const) USB_STR_2,
											  (uint_8_ptr const) USB_STR_n
										  };

USB_ALL_LANGUAGES g_languages = { USB_STR_0, sizeof(USB_STR_0),
									{ 
										(uint_16 const)0x0409,
                                   		(const uint_8 **)g_string_descriptors,
                                      	g_string_desc_size
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
 * @param type          : type of descriptor requested
 * @param sub_type      : string index for string descriptor
 * @param index         : string descriptor language Id
 * @param descriptor    : output descriptor pointer
 * @param size          : size of descriptor returned
 *
 * @return USB_OK                      When Successfull
 *         USBERR_INVALID_REQ_TYPE     when Error
 *****************************************************************************
 * This function is used to pass the pointer to the requested descriptor
 *****************************************************************************/
uint_8 USB_Desc_Get_Descriptor (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 type,            /* [IN] type of descriptor requested */
    uint_8 str_num,         /* [IN] string index for string descriptor */
    uint_16 index,          /* [IN] string descriptor language Id */
    uint_8_ptr *descriptor, /* [OUT] output descriptor pointer */
    USB_PACKET_SIZE *size   /* [OUT] size of descriptor returned */
)
{
    UNUSED (controller_ID)
    /* string descriptors are handled saperately */
    if (type == USB_STRING_DESCRIPTOR)
    {
        if(index == 0)
        {
            /* return the string and size of all languages */
            *descriptor = (uint_8_ptr)g_languages.languages_supported_string;
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
    else if (type < USB_MAX_STD_DESCRIPTORS+1)
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

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Interface
 *
 * @brief The function returns the alternate interface
 *
 * @param controller_ID : Controller Id
 * @param interface     : Interface number
 * @param alt_interface : Output alternate interface
 *
 * @return USB_OK                     When Successfull
 *         USBERR_INVALID_REQ_TYPE    when Error
 *****************************************************************************
 * This function is called by the framework module to get the current interface
 *****************************************************************************/
uint_8 USB_Desc_Get_Interface (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 interface,       /* [IN] interface number */
    uint_8_ptr alt_interface  /* [OUT] output alternate interface */
)
{
    UNUSED (controller_ID)
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
 * @param controller_ID : Controller Id
 * @param interface     : Interface number
 * @param alt_interface : Input alternate interface
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 * This function is called by the framework module to set the interface
 *****************************************************************************/
uint_8 USB_Desc_Set_Interface (
    uint_8 controller_ID, /* [IN] Controller ID */
    uint_8 interface,     /* [IN] interface number */
    uint_8 alt_interface  /* [IN] input alternate interface */
)
{
    UNUSED (controller_ID)
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set alternate interface*/
        g_alternate_interface[interface]=alt_interface;
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
 * @param controller_ID : Controller Id
 * @param config_val    : Configuration value
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************
 * This function checks whether the configuration is valid or not
 *****************************************************************************/
boolean USB_Desc_Valid_Configation (
    uint_8 controller_ID,/*[IN] Controller ID */
    uint_16 config_val   /*[IN] configuration value */
)
{
    uint_8 loop_index=0;
    UNUSED (controller_ID)
    
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
 * @param controller_ID : Controller Id
 * @param interface     : Target interface
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************
 * This function checks whether the interface is valid or not
 *****************************************************************************/
boolean USB_Desc_Valid_Interface (
    uint_8 controller_ID,   /*[IN] Controller ID */
    uint_8 interface        /*[IN] target interface */
)
{
    uint_8 loop_index=0;
    UNUSED (controller_ID)
    
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
 * @return REMOTE_WAKEUP_SUPPORT (TRUE) - if remote wakeup supported
 *****************************************************************************
 * This function returns remote wakeup is supported or not
 *****************************************************************************/
boolean USB_Desc_Remote_Wakeup (
    uint_8 controller_ID  /* [IN] Controller ID */
)
{
    UNUSED (controller_ID)
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
void* USB_Desc_Get_Endpoints (
    uint_8 controller_ID  /* [IN] Controller ID */
)
{
    UNUSED (controller_ID)
    return (void*)&usb_desc_ep;
}

/* EOF */
