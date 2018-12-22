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
 * @date May-08-2009
 *
 * @brief The file contains USB descriptors and functions
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "derivative.h"
#include "usb_descriptor.h"

#if (defined __MCF52xxx_H__)||(defined __MK_xxx_H__)
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST	const
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/ 
/* structure containing details of all the endpoints used by this device */ 
const USB_ENDPOINTS usb_desc_ep = { MSC_DESC_ENDPOINT_COUNT,
                                    {  
                                        {
                                            BULK_IN_ENDPOINT,
                                            USB_BULK_PIPE, 
                                            USB_SEND,
                                            BULK_IN_ENDP_PACKET_SIZE
                                        }, 
                                        {
                                            BULK_OUT_ENDPOINT,
                                            USB_BULK_PIPE, 
                                            USB_RECV,
                                            BULK_OUT_ENDP_PACKET_SIZE
                                        }        
                                    }
                                  };


uint_8 USB_DESC_CONST g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =  
{
    /* "Device Dexcriptor Size */
    DEVICE_DESCRIPTOR_SIZE,               
    /* "Device" Type of descriptor */   
    USB_DEVICE_DESCRIPTOR,                
    /*  BCD USB version  */  
    USB_uint_16_low(BCD_USB_VERSION), USB_uint_16_high(BCD_USB_VERSION),
    /* Device Class is indicated in the interface descriptors */   
    DEVICE_DESC_DEVICE_CLASS,
    /*  Device Subclass is indicated in the interface descriptors  */      
    DEVICE_DESC_DEVICE_SUBCLASS,
    /*  Device Protocol  */     
    DEVICE_DESC_DEVICE_PROTOCOL,
    /* Max Packet size */
    CONTROL_MAX_PACKET_SIZE,
    /* Vendor ID */
    0xA2,0x15,
    /* Product ID */
#if RAM_DISK_APP
    0x00,0x02,  
#elif SD_CARD_APP
    0x01,0x02,
#endif      
	  /* BCD Device version */
#if HIGH_SPEED_DEVICE
    0x00, 0x02,
#else
	  0x02,0x00,
#endif
    /* Manufacturer string index */
    0x01,     
    /* Product string index */  
    0x02,                        
    /*  Serial number string index */
    0x03,                  
    /*  Number of configurations */
    DEVICE_DESC_NUM_CONFIG_SUPPOTED                           
};

uint_8 USB_DESC_CONST g_config_descriptor[CONFIG_DESC_SIZE] =         
{   
    /* Configuration Descriptor Size - always 9 bytes*/
    CONFIG_ONLY_DESC_SIZE,
    USB_CONFIG_DESCRIPTOR,  					/* "Configuration" type of descriptor */   
    USB_uint_16_low(CONFIG_DESC_SIZE),
    USB_uint_16_high(CONFIG_DESC_SIZE),			/*  Total length of the Configuration descriptor */ 
    CONFIG_DESC_NUM_INTERFACES_SUPPOTED,		/*  NumInterfaces */   
    1,											/*  Configuration Value */      
    0,											/* Configuration Description String Index */  
    BUS_POWERED|SELF_POWERED|
    (REMOTE_WAKEUP_SUPPORT
    		<<REMOTE_WAKEUP_SHIFT),				/*  Attributes.support RemoteWakeup and self power */
    CONFIG_DESC_CURRENT_DRAWN, 					/*  Current draw from bus */
	
	/* INTERFACE DESCRIPTOR */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    0x00,										/* bInterfaceNumber */
    0x00,										/* bAlternateSetting */
    (uint_8)MSC_DESC_ENDPOINT_COUNT,			/* bNumEndpoints */
	MASS_STORAGE_CLASS,							/* Interface Class */	
	SCSI_TRANSPARENT_COMMAND_SET,				/* Interface Subclass*/
	BULK_ONLY_PROTOCOL,							/* Interface Protocol*/
    0x00,										/* Interface Description String Index*/

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    BULK_IN_ENDPOINT|(USB_SEND << 7),
    USB_BULK_PIPE, 
    USB_uint_16_low(BULK_IN_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_IN_ENDP_PACKET_SIZE),
    0x00,										/* This value is ignored for Bulk ENDPOINT */
    
    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    BULK_OUT_ENDPOINT|(USB_RECV << 7),
    USB_BULK_PIPE,
    USB_uint_16_low(BULK_OUT_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_OUT_ENDP_PACKET_SIZE),
    0x00 										/* This value is ignored for Bulk ENDPOINT */
};

#if HIGH_SPEED_DEVICE
	uint_8 USB_DESC_CONST g_device_qualifier_descriptor[DEVICE_QUALIFIER_DESCRIPTOR_SIZE] =
	{
	   /* Device Qualifier Descriptor Size */
	   DEVICE_QUALIFIER_DESCRIPTOR_SIZE, 
	   /* Type of Descriptor */
	   USB_DEVQUAL_DESCRIPTOR,           
       /*  BCD USB version  */  
       USB_uint_16_low(BCD_USB_VERSION), USB_uint_16_high(BCD_USB_VERSION),
	   /* bDeviceClass */
	   DEVICE_DESC_DEVICE_CLASS,
	   /* bDeviceSubClass */
	   DEVICE_DESC_DEVICE_SUBCLASS,      
	   /* bDeviceProtocol */
	   DEVICE_DESC_DEVICE_PROTOCOL,      
	   /* bMaxPacketSize0 */
	   CONTROL_MAX_PACKET_SIZE,          
	   /* bNumConfigurations */
	   DEVICE_DESC_NUM_CONFIG_SUPPOTED,  
	   /* Reserved : must be zero */ 
	   0x00                              
	};

uint_8 USB_DESC_CONST g_other_speed_config_descriptor[OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE] =
	{
	    CONFIG_ONLY_DESC_SIZE,     
	    /* This is a Other speed config descr */
	    USB_OTHER_SPEED_DESCRIPTOR,
        /*  Total length of the Configuration descriptor */   
        USB_uint_16_low(CONFIG_DESC_SIZE), USB_uint_16_high(CONFIG_DESC_SIZE),
	    CONFIG_DESC_NUM_INTERFACES_SUPPOTED,
	    /*value used to selct this configuration : Configuration Value */      
	    1, 
	    /*  Configuration Description String Index*/   
	    0, 
	    /*Attributes.support RemoteWakeup and self power*/
	    BUS_POWERED|SELF_POWERED|(REMOTE_WAKEUP_SUPPORT<<REMOTE_WAKEUP_SHIFT),	   
	    /*  Current draw from bus */
	    CONFIG_DESC_CURRENT_DRAWN, 
	   
		/* INTERFACE DESCRIPTOR */	
	    IFACE_ONLY_DESC_SIZE,
	    USB_IFACE_DESCRIPTOR,
	    /* bInterfaceNumber */
	    0x00,
	    /* bAlternateSetting */
	    0x00,
	    (uint_8)MSC_DESC_ENDPOINT_COUNT,     
		/* Interface Class */	  
		MASS_STORAGE_CLASS,
		  /* Interface Subclass*/	  
		SCSI_TRANSPARENT_COMMAND_SET,
		/* Interface Protocol*/
		BULK_ONLY_PROTOCOL, 
	    /* Interface Description String Index*/
	    0x00, 

	    /*Endpoint descriptor */
	    ENDP_ONLY_DESC_SIZE,
	    USB_ENDPOINT_DESCRIPTOR,
	    BULK_IN_ENDPOINT|(USB_SEND << 7),
	    USB_BULK_PIPE, 
	    USB_uint_16_low(BULK_IN_ENDP_PACKET_SIZE),
	    USB_uint_16_high(BULK_IN_ENDP_PACKET_SIZE),
	    0x00,/* This value is ignored for Bulk ENDPOINT */
	    
	    /*Endpoint descriptor */
	    ENDP_ONLY_DESC_SIZE,
	    USB_ENDPOINT_DESCRIPTOR,
	    BULK_OUT_ENDPOINT|(USB_RECV << 7),
	    USB_BULK_PIPE, 
	    USB_uint_16_low(BULK_OUT_ENDP_PACKET_SIZE),
	    USB_uint_16_high(BULK_OUT_ENDP_PACKET_SIZE),
	    0x00 /* This value is ignored for Bulk ENDPOINT */
	};
#endif

uint_8 USB_DESC_CONST USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =     
	{ sizeof(USB_STR_0),    
	  USB_STRING_DESCRIPTOR, 
	  0x09,
	  0x04/*equiavlent to 0x0409*/ 
	};
                                    
/*  Manufacturer string */                                    
uint_8 USB_DESC_CONST USB_STR_1[USB_STR_1_SIZE+USB_STR_DESC_SIZE] = 
	{  sizeof(USB_STR_1),          
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

/*  Product string */
#if RAM_DISK_APP
uint_8 USB_DESC_CONST USB_STR_2[USB_STR_2_SIZE+USB_STR_DESC_SIZE] =        
	{  sizeof(USB_STR_2),          
	   USB_STRING_DESCRIPTOR,                                
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
	   'M',0,
	   'A',0,
	   'S',0,
	   'S',0,
	   ' ',0,
	   'S',0,
	   'T',0,
	   'O',0,
	   'R',0,
	   'A',0,
	   'G',0,
	   'E',0
	};
#elif SD_CARD_APP
uint_8 USB_DESC_CONST USB_STR_2[USB_STR_2_SIZE+USB_STR_DESC_SIZE] =        
	{  sizeof(USB_STR_2),          
	   USB_STRING_DESCRIPTOR,                                
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
	   'S',0,
	   'D',0,
	   ' ',0,
	   'C',0,
	   'A',0,
	   'R',0,
	   'D',0,
	   ' ',0,
	   'R',0,
	   'E',0,
	   'A',0,
	   'D',0,
	   'E',0,
	   'R',0
	};
#endif

/*  Serial number string */
uint_8 USB_DESC_CONST USB_STR_3[USB_STR_3_SIZE+USB_STR_DESC_SIZE] = 
	{  sizeof(USB_STR_3),          
	   USB_STRING_DESCRIPTOR,                                
	   '0',0,
	   '1',0,
	   '2',0,
	   '3',0,
	   '4',0,
	   '5',0,
	   '6',0,
	   '7',0,
	   '8',0,
	   '9',0,
	   'A',0,
	   'B',0,
	   'C',0,
	   'D',0,
	   'E',0,
	   'F',0
	};                 

uint_8 USB_DESC_CONST USB_STR_n[USB_STR_n_SIZE+USB_STR_DESC_SIZE] =
	{  sizeof(USB_STR_n),         
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


uint_32 const g_std_desc_size[USB_MAX_STD_DESCRIPTORS+1] =
	{ 0,
	  DEVICE_DESCRIPTOR_SIZE,
	  CONFIG_DESC_SIZE,
	  0, /* string */
	  0, /* Interfdace */
	  0, /* Endpoint */
	  #if HIGH_SPEED_DEVICE
	 	DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
	 	OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE
	  #else                                     	
	     0, /* Device Qualifier */
	     0 /* other spped config */
	  #endif
	};   
                                             
uint_8 const *g_std_descriptors[USB_MAX_STD_DESCRIPTORS+1] = 
	{
	  NULL,
	  g_device_descriptor,
	  g_config_descriptor,
	  NULL, /* string */
	  NULL, /* Interfdace */
	  NULL, /* Endpoint */
	  #if HIGH_SPEED_DEVICE
	      g_device_qualifier_descriptor,
	      g_other_speed_config_descriptor
	  #else
	      NULL, /* Device Qualifier */
	      NULL /* other spped config*/
	  #endif
	}; 
   
uint_8 const g_string_desc_size[USB_MAX_STRING_DESCRIPTORS+1] = 
	{ sizeof(USB_STR_0),
	  sizeof(USB_STR_1),
	  sizeof(USB_STR_2),
	  sizeof(USB_STR_3),
	  sizeof(USB_STR_n)
	};   
                                             
uint_8 const *g_string_descriptors[USB_MAX_STRING_DESCRIPTORS+1] = 
	{ USB_STR_0,
	  USB_STR_1,
	  USB_STR_2,
	  USB_STR_3,
	  USB_STR_n
	};    
                                                                                                   
USB_ALL_LANGUAGES g_languages = 
	{ 
	  USB_STR_0, 
	  sizeof(USB_STR_0), 
      { 
        (uint_16 const)0x0409,
        (const uint_8 **)g_string_descriptors, g_string_desc_size
      }
    };

uint_8 const g_valid_config_values[USB_MAX_CONFIG_SUPPORTED+1] = {0,1};

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
 * @param controller_ID:        To identify the controller     
 * @param type:          type of descriptor requested     
 * @param str_num:       string index for string descriptor     
 * @param index:         string descriptor language Id     
 * @param descriptor:    output descriptor pointer
 * @param size:          size of descriptor returned
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint_8 USB_Desc_Get_Descriptor
(
    uint_8 controller_ID, 
    uint_8 type,
    uint_8 str_num, 
    uint_16 index,
    uint_8_ptr *descriptor,
    uint_32 *size
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
        } 
        else 
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
            *descriptor = (uint_8_ptr)
            	g_languages.usb_language[lang_id].lang_desc[lang_index];
            *size = 
            	g_languages.usb_language[lang_id].lang_desc_size[lang_index];
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
 * @param controller_ID:        To identify the controller:              
 * @param interface:      interface number     
 * @param alt_interface:  output alternate interface     
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint_8 USB_Desc_Get_Interface
(
	uint_8 controller_ID, 
    uint_8 interface, 
    uint_8_ptr alt_interface
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
 * @param controller_ID:        To identify the controller:              
 * @param interface:      interface number     
 * @param alt_interface:  input alternate interface     
 *
 * @return USB_OK                              When Successfull
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint_8 USB_Desc_Set_Interface
(
	uint_8 controller_ID, 
    uint_8 interface, 
    uint_8 alt_interface
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
 * @param controller_ID:        To identify the controller              
 * @param config_val      configuration value     
 *
 * @return TRUE           When Valid
 *         FALSE          When Error
 *****************************************************************************/
boolean USB_Desc_Valid_Configation(uint_8 controller_ID,uint_16 config_val)
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
 * @name  USB_Desc_Remote_Wakeup
 *
 * @brief The function checks whether the remote wakeup is supported or not
 *
 * @param controller_ID:        To identify the controller     
 *
 * @return REMOTE_WAKEUP_SUPPORT (TRUE) - if remote wakeup supported
 *****************************************************************************/
boolean USB_Desc_Remote_Wakeup(uint_8 controller_ID) 
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
 * @param controller_ID:        To identify the controller:              
 *
 * @return pointer to USB_ENDPOINTS
 *****************************************************************************/
USB_ENDPOINTS *USB_Desc_Get_Endpoints(uint_8 controller_ID) 
{
    UNUSED (controller_ID) 
    return &usb_desc_ep;
}         

/* EOF */
