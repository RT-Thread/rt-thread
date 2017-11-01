/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @brief The file contains USB descriptors for Mouse Application
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_class.h"
#include "usb_descriptor.h"
#ifdef MCU_mcf51jf128
#include "Flash_FTFL.h"
#endif
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
#if defined(__MCF52xxx_H__) || defined(__MK_xxx_H__)
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST	const
#endif
/* structure containing details of all the endpoints used by this device */
USB_DESC_CONST USB_ENDPOINTS usb_desc_runtime_ep = { HID_DESC_ENDPOINT_COUNT,
		{HID_ENDPOINT,
				USB_INTERRUPT_PIPE,
				USB_SEND,
				HID_ENDPOINT_PACKET_SIZE
		}
};

USB_DESC_CONST USB_ENDPOINTS usb_desc_dfu_ep = { DFU_DESC_ENDPOINT_COUNT };
uint_8 USB_DESC_CONST g_device_runtime_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    DEVICE_DESCRIPTOR_SIZE,               /* "Device Descriptor Size        */
    USB_DEVICE_DESCRIPTOR,                /* "Device" Type of descriptor    */
    0x00, 0x02,                           /*  BCD USB version               */
    0x00,                                 /*  Device Class is indicated in
                                             the interface descriptors     */
    0x00,                                 /*  Device Subclass is indicated
                                             in the interface descriptors  */
    0x00,                                 /*  Device Protocol               */
    CONTROL_MAX_PACKET_SIZE,              /*  Max Packet size               */
    0xA2,0x15,                            /*  Vendor ID                     */
    0x00,0x05,                            /*  Product ID                    */
    0x02,0x00,                            /*  BCD Device version            */
    0x01,                                 /*  Manufacturer string index     */
    0x02,                                 /*  Product string index          */
    0x00,                                 /*  Serial number string index    */
    0x01                                  /*  Number of configurations      */
};

uint_8 USB_DESC_CONST g_device_dfu_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    DEVICE_DESCRIPTOR_SIZE,               /* "Device Descriptor Size        */
    USB_DEVICE_DESCRIPTOR,                /* "Device" Type of descriptor    */
    0x00, 0x02,                           /*  BCD USB version               */
    0x00,                                 /*  Device Class is indicated in
                                             the interface descriptors     */
    0x00,                                 /*  Device Subclass is indicated
                                             in the interface descriptors  */
    0x00,                                 /*  Device Protocol               */
    CONTROL_MAX_PACKET_SIZE,              /*  Max Packet size               */
    0xA2,0x15,                          /*  Vendor ID                     */
    0x00,0x10,                            /*  Product ID                    */
    0x02,0x00,                            /*  BCD Device version            */
    0x01,                                 /*  Manufacturer string index     */
    0x03,                                 /*  Product string index          */
    0x00,                                 /*  Serial number string index    */
    0x01                                  /*  Number of configurations      */
};
uint_8 USB_DESC_CONST g_config_runtime_descriptor[CONFIG_DESC_SIZE_RUNTIME] =
{
    CONFIG_ONLY_DESC_SIZE,       /*  Configuration Descriptor Size - always 9 bytes*/
    USB_CONFIG_DESCRIPTOR,       /* "Configuration" type of descriptor */
    CONFIG_DESC_SIZE_RUNTIME, 0x00,     /*  Total length of the Configuration descriptor */
    2,                           /*  NumInterfaces */
    1,                           /*  Configuration Value */
    0,                           /*  Configuration Description String Index*/
    BUS_POWERED|SELF_POWERED|(REMOTE_WAKEUP_SUPPORT<<REMOTE_WAKEUP_SHIFT),
    /* S08/CFv1 are both self powered (its compulsory to set bus powered)*/
    /*Attributes.support RemoteWakeup and self power*/
    0x32,                        /*  Current draw from bus */

    /* Interface Descriptor0 */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x00,
    0x00,
    HID_DESC_ENDPOINT_COUNT,
    0x03,
    0x01,
    0x02,
    0x00,

    /* HID descriptor */
    HID_ONLY_DESC_SIZE,
    USB_HID_DESCRIPTOR,
    0x00,0x01,
    0x00,
    0x01,
    0x22,
    0x34,0x00,
    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    HID_ENDPOINT|(USB_SEND << 7),
    USB_INTERRUPT_PIPE,
    HID_ENDPOINT_PACKET_SIZE, 0x00,
    0x0A,

    /* Interface Descriptor 1*/
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x01,
    0x00,
    0x00,
    0xFE,  /*    bInterfaceClass */
    0x01,  /*     bInterfaceSubClass */
    0x01,   /* bInterfaceProtocol   */
    0x03,      /*   String index */

    /* Functional descriptor  */
    FUNCTIONAL_DESC_SIZE,                            /* Functional descriptor size */
    USB_DFU_FUNCTIONAL_DESCRIPTOR,                       /* Functional descriptor type */
    (DETACH<<3)|(MANIFESTATION<<2)|(BITCANUPLOAD<<1)|BITCANDOWNLOAD,/*  bmAttributes */
    0x64,0x00,                                       /* wDetachTimeOut   */
    MAX_BLOCK_SIZE,0x00, 			                 /* wTransferSize IN BYTES */
    0x10,0x01                                        /* bcdDFUVersion */

};

uint_8 USB_DESC_CONST g_config_dfu_descriptor[CONFIG_DESC_SIZE_DFU] =
{
    CONFIG_ONLY_DESC_SIZE,     /*  Configuration Descriptor Size - always 9 bytes*/
    USB_CONFIG_DESCRIPTOR,     /* "Configuration" type of descriptor */
    CONFIG_DESC_SIZE_DFU, 0x00,/*  Total length of the Configuration descriptor */
    0x01,                      /*  NumInterfaces */
    0x01,                      /*  Configuration Value */
    0x00,                      /*  Configuration Description String Index*/
    BUS_POWERED|SELF_POWERED|(REMOTE_WAKEUP_SUPPORT<<REMOTE_WAKEUP_SHIFT),
    /* S08/CFv1 are both self powered (its compulsory to set bus powered)*/
    /*Attributes.support RemoteWakeup and self power*/
    0x32,                      /*  Current draw from bus */

    /* Interface Descriptor */
    IFACE_ONLY_DESC_SIZE,      /*  Interface Descriptor  Size - always 9 bytes*/
    USB_IFACE_DESCRIPTOR,      /*  type of descriptor */
    0x00,                      /*  bInterfaceNumbe */
    0x00,                      /*  bAlternateSetting */
    0x00,                      /*  bNumEndpoints (only control endpoint */
    0xFE,                      /*  bInterfaceClass */
    0x01,                      /*  bInterfaceSubClass */
    0x02,                      /*  bInterfaceProtocol */
    0x00,                      /*  Index of String Descriptor Describing this interface */

    /* Functional descriptor  */
    FUNCTIONAL_DESC_SIZE,                                                 /* Functional descriptor size */
    USB_DFU_FUNCTIONAL_DESCRIPTOR,                                            /* Functional descriptor type */
    (DETACH<<3)|(MANIFESTATION<<2)|(BITCANUPLOAD<<1)|BITCANDOWNLOAD,      /*  bmAttributes */
    0x64,0x00,                                                            /* wDetachTimeOut   */
    MAX_BLOCK_SIZE,0x00,                                                  /* wTransferSize IN BYTES */
    0x10,0x01,                                                            /* bcdDFUVersion */
};


uint_8 USB_DESC_CONST g_report_descriptor[REPORT_DESC_SIZE] =
{
    0x05, 0x01,   /* Usage Page (Generic Desktop)*/
    0x09, 0x02,   /* Usage (Mouse) */
    0xA1, 0x01,   /* Collection (Application) */
    0x09, 0x01,   /* Usage (Pointer) */

    0xA1, 0x00,   /* Collection (Physical) */
    0x05, 0x09,   /* Usage Page (Buttons) */
    0x19, 0x01,   /* Usage Minimun (01) */
    0x29, 0x03,   /* Usage Maximum (03) */

    0x15, 0x00,   /* logical Minimun (0) */
    0x25, 0x01,   /* logical Maximum (1) */
    0x95, 0x03,   /* Report Count (3) */
    0x75, 0x01,   /* Report Size (1) */

    0x81, 0x02,   /* Input(Data, Variable, Absolute) 3 button bits */
    0x95, 0x01,   /* Report count (1) */
    0x75, 0x05,   /* Report Size (5) */
    0x81, 0x01,   /* Input (Constant), 5 bit padding */

    0x05, 0x01,   /* Usage Page (Generic Desktop) */
    0x09, 0x30,   /* Usage (X) */
    0x09, 0x31,   /* Usage (Y) */
    0x09, 0x38,   /* Usage (Z) */

    0x15, 0x81,   /* Logical Minimum (-127) */
    0x25, 0x7F,   /* Logical Maximum (127) */
    0x75, 0x08,   /* Report Size (8) */
    0x95, 0x03,   /* Report Count (2) */

    0x81, 0x06,   /* Input(Data, Variable, Relative), 2 position bytes (X & Y)*/
    0xC0,         /* end collection */
    0xC0          /* end collection */
};

uint_8 USB_DESC_CONST USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =
    {sizeof(USB_STR_0),
     USB_STRING_DESCRIPTOR,
     0x09,
     0x04 /*equiavlent to 0x0409*/
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
     'M',0,
     'O',0,
     'U',0,
     'S',0,
     'E',0,
     ' ',0,
     'D',0,
     'E',0,
     'M',0,
     'O',0,
     ' ',0
  };
uint_8 USB_DESC_CONST USB_STR_3[USB_STR_3_SIZE+USB_STR_DESC_SIZE]
= {  sizeof(USB_STR_3),
     USB_STRING_DESCRIPTOR,
     ' ',0,
     'D',0,
     'F',0,
     'U',0,
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

USB_PACKET_SIZE  *g_std_desc_size;
uint_8_ptr  *g_std_descriptors;

USB_PACKET_SIZE  g_std_desc_runtime_size[USB_MAX_STD_DESCRIPTORS+1] =
    {0,
     DEVICE_DESCRIPTOR_SIZE,
     CONFIG_DESC_SIZE_RUNTIME,
     0, /* string */
     0, /* Interface */
     0, /* Endpoint */
     0, /* Device Qualifier */
     0, /* other speed config */
     REPORT_DESC_SIZE
    };

uint_8_ptr  g_std_runtime_descriptors[USB_MAX_STD_DESCRIPTORS+1] =
{
    NULL,
    (uint_8_ptr)g_device_runtime_descriptor,
    (uint_8_ptr)g_config_runtime_descriptor,
    NULL, /* string */
    NULL, /* Interface */
    NULL, /* Endpoint */
    NULL, /* Device Qualifier */
    NULL, /* other speed config*/
    (uint_8_ptr)g_report_descriptor
};

USB_PACKET_SIZE  g_std_desc_dfu_size[USB_MAX_STD_DESCRIPTORS+1] =
    {0,
     DEVICE_DESCRIPTOR_SIZE,
     CONFIG_DESC_SIZE_DFU,
     0, /* string */
     0, /* Interface */
     0, /* Endpoint */
     0, /* Device Qualifier */
     0, /* other speed config */

    };

uint_8_ptr  g_std_dfu_descriptors[USB_MAX_STD_DESCRIPTORS+1] =
{
    NULL,
    (uint_8_ptr)g_device_dfu_descriptor,
    (uint_8_ptr)g_config_dfu_descriptor,
    NULL, /* string */
    NULL, /* Interface */
    NULL, /* Endpoint */
    NULL, /* Device Qualifier */
    NULL, /* other speed config*/

};
uint_8 USB_DESC_CONST g_string_desc_size[USB_MAX_STRING_DESCRIPTORS+1] =
    {sizeof(USB_STR_0),
     sizeof(USB_STR_1),
     sizeof(USB_STR_2),
     sizeof(USB_STR_3),
     sizeof(USB_STR_n)
    };

uint_8_ptr USB_DESC_CONST g_string_descriptors[USB_MAX_STRING_DESCRIPTORS+1] =
{
    (uint_8_ptr const) USB_STR_0,
    (uint_8_ptr const) USB_STR_1,
    (uint_8_ptr const) USB_STR_2,
    (uint_8_ptr const) USB_STR_3,
    (uint_8_ptr const) USB_STR_n
};

USB_ALL_LANGUAGES g_languages = { USB_STR_0, sizeof(USB_STR_0),
    {
        (uint_16 const)0x0409,
        (const uint_8 **)g_string_descriptors,
        g_string_desc_size
    }
};

uint_8 USB_DESC_CONST g_valid_config_values[USB_MAX_CONFIG_SUPPORTED+1]={0,1};

/****************************************************************************
 * Global Variables
 ****************************************************************************/
uint_8 mode = RUNTIME_MODE;
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
static uint_8 g_alternate_interface[USB_MAX_SUPPORTED_INTERFACES];
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
uint_8 USB_Desc_Get_Descriptor
(
    uint_8 controller_ID,   /* [IN]  Controller ID */
    uint_8 type,            /* [IN]  Type of descriptor requested */
    uint_8 str_num,         /* [IN]  String index for string descriptor */
    uint_16 index,          /* [IN]  String descriptor language Id */
    uint_8_ptr *descriptor, /* [OUT] Output descriptor pointer */
    USB_PACKET_SIZE *size   /* [OUT] Size of descriptor returned */
)
{
    UNUSED (controller_ID)
    if (mode == RUNTIME_MODE )
    {
        g_std_descriptors  =  g_std_runtime_descriptors;
        g_std_desc_size    =  g_std_desc_runtime_size;
    }
    else
    {
        g_std_descriptors  =  g_std_dfu_descriptors;
        g_std_desc_size    =  g_std_desc_dfu_size;
    }
    switch (type)
    {
    case USB_REPORT_DESCRIPTOR:
    {
        type = USB_MAX_STD_DESCRIPTORS;
        *descriptor = (uint_8_ptr)g_std_descriptors [type];
        *size = g_std_desc_size[type];
    }
    break;
    case USB_HID_DESCRIPTOR: /* hid descriptor and functional descriptor has the same index (0x21)*/
    {
        type = USB_CONFIG_DESCRIPTOR ;
        *descriptor = (uint_8_ptr)(g_std_descriptors [type]+
                                   CONFIG_ONLY_DESC_SIZE+IFACE_ONLY_DESC_SIZE);
        *size = HID_ONLY_DESC_SIZE;
    }
    break;
    case USB_STRING_DESCRIPTOR:
    {
        if (index == 0)
        {
            /* return the string and size of all languages */
            *descriptor = (uint_8_ptr)g_languages.
                          languages_supported_string;
            *size = g_languages.languages_supported_size;
        } else
        {
            uint_8 lang_id=0;
            uint_8 lang_index=USB_MAX_LANGUAGES_SUPPORTED;

            for (;lang_id< USB_MAX_LANGUAGES_SUPPORTED;lang_id++)
            {
                /* check whether we have a string for this language */
                if (index == g_languages.usb_language[lang_id].language_id)
                {   /* check for max descriptors */
                    if (str_num < USB_MAX_STRING_DESCRIPTORS)
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
            if (*descriptor == NULL)
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
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *This function is called by the framework module to get the current interface
 *****************************************************************************/
uint_8 USB_Desc_Get_Interface
(
    uint_8 controller_ID,     /* [IN] Controller ID */
    uint_8 interface,         /* [IN] Interface number */
    uint_8_ptr alt_interface  /* [OUT] Output alternate interface */
)
{
    UNUSED (controller_ID)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
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
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************
 *This function is called by the framework module to set the interface
 *****************************************************************************/
uint_8 USB_Desc_Set_Interface
(
    uint_8 controller_ID, /* [IN] Controller ID */
    uint_8 interface,     /* [IN] Interface number */
    uint_8 alt_interface  /* [IN] Input alternate interface */
)
{
    UNUSED (controller_ID)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
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
boolean USB_Desc_Valid_Configation
(
    uint_8 controller_ID,/*[IN] Controller ID */
    uint_16 config_val   /*[IN] Configuration value */
)
{
    uint_8 loop_index=0;
    UNUSED (controller_ID)

    /* check with only supported val right now */
    while (loop_index < (USB_MAX_CONFIG_SUPPORTED+1))
    {
        if (config_val == g_valid_config_values[loop_index])
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
boolean USB_Desc_Valid_Interface
(
    uint_8 controller_ID, /*[IN] Controller ID */
    uint_8 interface      /*[IN] Target interface */
)
{
    uint_8 loop_index=0;
    UNUSED (controller_ID)

    /* check with only supported val right now */
    while (loop_index < USB_MAX_SUPPORTED_INTERFACES)
    {
        if (interface == g_alternate_interface[loop_index])
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
boolean USB_Desc_Remote_Wakeup
(
    uint_8 controller_ID      /* [IN] Controller ID */
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
void* USB_Desc_Get_Endpoints
(
    uint_8 controller_ID      /* [IN] Controller ID */
)
{
    UNUSED (controller_ID)

    if (mode == RUNTIME_MODE)
        return (void*)&usb_desc_runtime_ep;
    else
        return (void*)&usb_desc_dfu_ep;
}
/****************************************************************************/
uint_8 s_dnload[MAX_FIRMWARE_SIZE];           /* DNload Data */
uint_8 firmware_block[MAX_BLOCK_SIZE];        /* Firmware block */
uint_8 buffer[MAX_BLOCK_SIZE];                /* Buffer for upload block */
uint_16 firmware_size;                        /* Size of firmware */
uint_16 firmware_offset;                      /* firmware offset */
uint_8 Final_Block;                           /* Final block of new firmware */
/* Addreses of Flash area */
#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H))
unsigned long *firmware_address = (unsigned long *)0x00020410;
unsigned long *manifest_address = (unsigned long *)0x00021510;
unsigned long *firmware_size_address = (unsigned long *)(0x00021510+MAX_FIRMWARE_SIZE);
#elif(defined(_MC9S08MM128_H)||defined(_MC9S08JE128_H))
unsigned char *firmware_address = (unsigned char *)0x8000;
unsigned char *manifest_address = (unsigned char *)0x8D00;
unsigned char *firmware_size_address = (unsigned char *)(0x8D00+MAX_FIRMWARE_SIZE);
#elif defined(_MCF51JM128_H)
	unsigned long *firmware_address = (unsigned long *)0x0001E000;
	unsigned long *manifest_address = (unsigned long *)0x0001F000;
	unsigned long *firmware_size_address = (unsigned long *)(0x0001FF00);
#elif defined(__MCF52xxx_H__)
	#if defined(USED_EXTERNAL_FLASH)
	unsigned char *firmware_address = (unsigned char *)0x2000;
	unsigned char *manifest_address = (unsigned char *)0x6000;
	unsigned char *firmware_size_address = (unsigned char *)(0x2300);
	#else
	unsigned long *firmware_address = (unsigned long *)0x0001E000;
	unsigned long *manifest_address = (unsigned long *)0x0001F000;
	unsigned long *firmware_size_address = (unsigned long *)(0x0001FF00);
	#endif
#elif defined (_MC9S08JM60_H)
unsigned char *firmware_address = (unsigned char *)0xF000;
unsigned char *manifest_address = (unsigned char *)0xFAB0;
unsigned char *firmware_size_address = (unsigned char *)(0xFC00+MAX_FIRMWARE_SIZE);
#elif (defined (_MC9S08JM16_H)||defined (_MC9S08JS16_H))
unsigned char *firmware_address = (unsigned char *)0xFA00;
unsigned char *manifest_address = (unsigned char *)0xFB00;
unsigned char *firmware_size_address = (unsigned char *)(0xFC00+MAX_FIRMWARE_SIZE);
#elif (defined (__MK_xxx_H__)|| defined (MCU_mcf51jf128))
volatile uint_32 firmware_address =	0x14000;
volatile uint_32 manifest_address = 	0x15000;
volatile uint_32 firmware_size_address = 0x15000 + MAX_FIRMWARE_SIZE ;
#endif
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Dnload
 *
 * @brief   The funtion is called to downloaded firmware image from host to
 *          device
 *
 * @param controller_ID     : Controller ID
 * @param wBlockNum         : wBlockNum
 * @param data              : Pointer to data
 * @param size              : Pointer to size of data
 *
 * @return status:
 *                        USB_OK  : When Successfull
 *                        Other   : When Error
 *
 ******************************************************************************
 * Download firmware image from host to device to upgrade
 *****************************************************************************/
uint_8 USB_Class_DFU_Dnload
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 wBlockNum,                   /* [IN] The BlockNum of firmware image */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 i;
    uint_32 timeout;
    UNUSED(controller_ID)
    if (*size == 0)
	    {
	        /* PwPollTimeOut for manifestation phase */
	        timeout = (uint_32)(MAX_BLOCK_SIZE*(wBlockNum+1));
	        USB_Class_DFU_set_bwPoll_TimeOut(timeout);
	    }
	 else
	 	{
	 		timeout = (uint_32)*size;
		    USB_Class_DFU_set_bwPoll_TimeOut(timeout);
		    if ((wBlockNum * MAX_BLOCK_SIZE) > MAX_FIRMWARE_SIZE)
		    {
		    	return USBERR_INVALID_REQ_TYPE;
		    }

		    Final_Block = wBlockNum;
		    if (wBlockNum == 0)
		    {
		       (void)USB_Class_DFU_App_Reset_Flag_Manifest();
		       firmware_size = 0;
		    }
		    for (i=0;i<*size;i++)
		    {
		#if (STORAGE_FIRMWARE == TRUE)          /* Check storage mode */
		        firmware_block[i] = *(uint_8_ptr)(*data+i);
		#else
		        s_dnload[wBlockNum*MAX_BLOCK_SIZE+i]=*(*data+i);
		#endif
		    }
		    firmware_size += *size;
	 	}
    return USB_OK;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Flashing
 *
 * @brief   This function erase a sector in flash memory at
 *			manifest_address,firmware_address.
 *			Write the data block received at DFU_Dnload_Sync_State to flash memory.
 *
 * @param 	none
 *
 * @return 	none
 *
 ******************************************************************************
 *
 *****************************************************************************/
void USB_Class_DFU_Flashing(void)
{

#if (STORAGE_FIRMWARE == TRUE)          /* Check storage mode */
	DisableInterrupts;
	    if (Final_Block == 0)
	    {
			(void)Flash_SectorErase(firmware_address);
	    }
	#if (defined (_MC9S08_H)|| defined (USED_EXTERNAL_FLASH)|| defined(__MK_xxx_H__))||(defined MCU_mcf51jf128)
	    (void)Flash_ByteProgram(firmware_address+Final_Block*MAX_BLOCK_SIZE,firmware_block,MAX_BLOCK_SIZE);
	#else
	    (void)Flash_ByteProgram(firmware_address+Final_Block*MAX_BLOCK_SIZE/4,(uint_32_ptr)firmware_block,MAX_BLOCK_SIZE);
	#endif
	EnableInterrupts;
#endif

}

uint_16 firmware_offset;
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Upload
 *
 * @brief   The function is called to uploaded firmware image from device to
 *          host
 *
 * @param controller_ID     : Controller ID
 * @param BlockNum          : BlockNum
 * @param data              : Pointer to data
 * @param size              : Pointer to size of data
 *
 * @return status:
 *                        USB_OK : When Successfull
 *                        Other  : When Error
 *
 ******************************************************************************
 * Upload firmware image from device to host
 *****************************************************************************/
uint_8 USB_Class_DFU_Upload
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 BlockNum,                    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size,              /* [OUT] Pointer to Size of Data */
    USB_PACKET_SIZE wLength             /* [IN] wLength */
)
{
    uint_8 i;
    UNUSED(controller_ID)
    /* if interface valid */
    if (BlockNum == 0)
    {
    	firmware_offset = 0;
#if (defined(_MCF51_H)||defined(__MCF52xxx_H__))
    #if defined(USED_EXTERNAL_FLASH)
        if(*firmware_size_address == 0xFF)
    	      return  USBERR_INVALID_REQ_TYPE;
    	  else
    	      firmware_size = (uint_16)(*(uint_16*)(firmware_size_address));
    #else
    	  if(*firmware_size_address == 0xFFFFFFFF)
    	      return  USBERR_INVALID_REQ_TYPE;
    	  else
    	      firmware_size = ((*firmware_size_address)>>16);
    #endif
#else
    if((uint_8)(*(uint_8*)firmware_size_address) == 0xFF)
    	  return  USBERR_INVALID_REQ_TYPE;
    else
    	  firmware_size = (uint_16)(*(uint_16*)(firmware_size_address));
#endif
    }
    /* Calculate size of response frame */
    if((firmware_size - firmware_offset) >= wLength)
    {
    	*size = wLength;
    }
    else
    {
    	*size = (USB_PACKET_SIZE)(firmware_size - firmware_offset);
    }

    /* prepare data to response */
    for (i=0;i<*size;i++)
    {
        buffer[i] = *(uint_8 *)((uint_8 *)manifest_address + firmware_offset + i) ;
    }

    /* update firmware offset */
  	firmware_offset = (uint_16)(firmware_offset + wLength);
    *data = buffer;

    return USB_OK;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Manifest
 *
 * @brief   The function is called to implemented manifestation phase process
 *
 * @param none
 *
 * @return none
 *
 ******************************************************************************
 * Upload firmware image
 *****************************************************************************/
	void USB_Class_DFU_Manifest(void)
	{
		DisableInterrupts;
	#if (STORAGE_FIRMWARE == TRUE)
		#if ((!defined(USED_EXTERNAL_FLASH)) && (!defined(_MC9S08JS16_H) ) && (!defined(_MC9S08JM16_H) ) )
		(void)Flash_SectorErase(manifest_address);
		#endif
	#else
		(void)Flash_SectorErase(manifest_address);
	#endif
		/* Check storage mode */
	#if (STORAGE_FIRMWARE == TRUE)
		(void)Flash_ByteProgram(manifest_address,firmware_address,firmware_size);
	#else
		(void)Flash_ByteProgram(manifest_address,(unsigned long *)s_dnload,firmware_size);
	#endif
	#if (defined (_MC9S08_H)|| defined(_MCF51JM128_H)||defined(_MCF52221_H_))
		(void)Flash_SectorErase(firmware_size_address);
	#endif
		(void)Flash_ByteProgram(firmware_size_address,(uint_32_ptr)(&firmware_size),2);
		EnableInterrupts;
		USB_Class_DFU_App_Set_Flag_Manifest();
	}
/*end of file*/
