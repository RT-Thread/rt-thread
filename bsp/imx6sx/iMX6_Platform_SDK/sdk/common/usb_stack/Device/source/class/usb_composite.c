/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_composite.c
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains USB composite layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_composite.h"  /* USB Video Class Header File */
#include "usb_devapi.h"   	/* USB device Header File */
#include "usb_framework.h"  /* USB device Header File */
#ifdef USE_HID_CLASS
    #include "usb_hid.h"
#endif
#ifdef USE_MSD_CLASS
    #include "usb_msc.h"
#endif
#ifdef USE_AUDIO_CLASS
    #include "usb_audio.h"
#endif
#ifdef USE_VIDEO_CLASS
    #include "usb_video.h"
#endif
#ifdef USE_PHDC_CLASS
    #include "usb_phdc.h"
#endif
#ifdef USE_CDC_CLASS
    #include "usb_cdc.h"
#endif
#ifdef USE_CDC_CLASS
    #include "usb_dfu.h"
#endif

/*****************************************************************************
 * Local functions prototypes
 *****************************************************************************/ 
static void USB_Composite_Event (
    uint_8 controller_ID,  
    uint_8 event,          
    void* val              
);

static uint_8 USB_Composite_Other_Requests (
    uint_8 controller_ID,               
    USB_SETUP_STRUCT * setup_packet,    
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);

/*****************************************************************************
 * Global functions
 *****************************************************************************/ 

 /**************************************************************************//*!
 *
 * @name  USB_Composite_Init
 *
 * @brief   The funtion initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   composite_callback_ptr      : Pointer to app callback  
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the Composite layer
 *****************************************************************************/ 
uint_8 USB_Composite_Init(
    uint_8    controller_ID,                            /* [IN] Controller ID */
    COMPOSITE_CALLBACK_STRUCT * composite_callback_ptr   /* [IN] Pointer to class info */
)
{    
    uint_8 count,status;
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;   
    
    /* Get device architecture */
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);
    
    /* Device init */
    status = _usb_device_init(controller_ID, NULL,
        (uint_8)(dev_arc_ptr->ep_count+1), TRUE);
        
    if(status == USB_OK)
    {
        /* Initialize the generic class functions */
        status = USB_Class_Init(controller_ID,USB_Composite_Event,
            USB_Composite_Other_Requests);
        if(status == USB_OK)
        {   
            for(count = 0; count < dev_arc_ptr->cl_count; count++)
            {
                dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
                /* Initializes sub_classes */
                switch(dev_class_ptr->class_type)  
                {
#ifdef USE_HID_CLASS 
                    case HID_COMP_CC:
                        (void)USB_Class_HID_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_specific_callback);   
                        break;
#endif
#ifdef USE_AUDIO_CLASS
                    case AUDIO_COMP_CC:
                        (void)USB_Class_Audio_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_callback);   

                        break;
                    #endif
#ifdef USE_VIDEO_CLASS
                    case VIDEO_COMP_CC:
                        (void)USB_Class_Video_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_callback);  

                        break;
#endif
#ifdef USE_CDC_CLASS
                    case CDC_COMP_CC:                            
                        (void)USB_Class_CDC_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_callback, TRUE);      
                        break;
#endif
#ifdef USE_MSD_CLASS
                    case MSD_COMP_CC:
                        (void)USB_Class_MSC_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_callback); 
                        break;
#endif
#ifdef USE_PHDC_CLASS
                    case PHDC_COMP_CC:
                        (void)USB_Class_PHDC_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback); 
                        break;
#endif
#ifdef USE_DFU_CLASS
                    case DFU_COMP_CC:
                        (void)USB_Class_Dfu_Init(
                            controller_ID,composite_callback_ptr->class_app_callback[count]->composite_class_callback,
                            composite_callback_ptr->class_app_callback[count]->vendor_req_callback,
                            composite_callback_ptr->class_app_callback[count]->param_callback); 
                        break;
#endif
                    default:
                        break;
                }
            }
        }
    }
    return status;   
}

 /**************************************************************************//*!
 *
 * @name  USB_Composite_DeInit
 *
 * @brief   The funtion De-initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   composite_callback_ptr      : Pointer to app callback  
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function De-initializes the Composite layer
 *****************************************************************************/ 
uint_8 USB_Composite_DeInit(
    uint_8    controller_ID                           /* [IN] Controller ID */
)
{    
    uint_8 count,status = USB_OK;
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;   
    
     /* Call common class deinit function */
    status = USB_Class_DeInit(controller_ID);
    
    if(status == USB_OK)
    /* Call device deinit function */
    	status = _usb_device_deinit();
    
    /* Get device architecture */
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);
    for(count = 0; count < dev_arc_ptr->cl_count; count++)
    {
        /* Initializes sub_classes */
        dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
        switch(dev_class_ptr->class_type)  
        {
#ifdef USE_HID_CLASS
            case HID_COMP_CC:
                status = USB_Class_HID_DeInit(controller_ID);
            break;
#endif
#ifdef USE_AUDIO_CLASS    
            case AUDIO_COMP_CC:
               status = USB_Class_Audio_DeInit(controller_ID);
            break;
#endif
#ifdef USE_VIDEO_CLASS     
            case VIDEO_COMP_CC:
                status = USB_Class_Video_DeInit(controller_ID);
            break;
#endif
#ifdef USE_CDC_CLASS    
            case CDC_COMP_CC:
                status = USB_Class_CDC_DeInit(controller_ID);
                break;
#endif
#ifdef USE_MSD_CLASS    
            case MSD_COMP_CC:
                status = USB_Class_MSC_DeInit(controller_ID);
                break;
#endif
#ifdef USE_PHDC_CLASS
            case PHDC_COMP_CC:
                status = USB_Class_PHDC_DeInit(controller_ID);
                break;
#endif
#ifdef USE_DFU_CLASS
            case DFU_COMP_CC:
                status = USB_Class_HID_DeInit(controller_ID);
                break;
        #endif
        }
    }
    return status;    
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_Event
 *
 * @brief The funtion initializes composite endpoint
 *
 * @param controller_ID     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * 
 *****************************************************************************/
void USB_Composite_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */
)
{   
    uint_8 count;
    
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;  
    
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);

    for(count = 0; count < dev_arc_ptr->cl_count; count++)
    {
        /* Initializes sub_classes */
        dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
        switch(dev_class_ptr->class_type)  
        {
#ifdef USE_HID_CLASS
            case HID_COMP_CC:
                USB_Class_Hid_Event(controller_ID,event,val);
            break;
#endif
#ifdef USE_AUDIO_CLASS    
            case AUDIO_COMP_CC:
                USB_Class_Audio_Event(controller_ID,event,val);
            break;
#endif
#ifdef USE_VIDEO_CLASS     
            case VIDEO_COMP_CC:
                USB_Class_Video_Event(controller_ID,event,val);
            break;
#endif
#ifdef USE_CDC_CLASS    
            case CDC_COMP_CC:
                USB_Class_CDC_Event(controller_ID,event,val);
                break;
#endif
#ifdef USE_MSD_CLASS    
            case MSD_COMP_CC:
                USB_Class_MSC_Event(controller_ID,event,val);
                break;
#endif
#ifdef USE_PHDC_CLASS
            case PHDC_COMP_CC:
                USB_Class_PHDC_Event(controller_ID,event,val);
                break;
#endif
#ifdef USE_DFU_CLASS
            case DFU_COMP_CC:
                USB_Class_Hid_Event(controller_ID,event,val);
                break;
        #endif
        }
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_Other_Requests
 *
 * @brief   The funtion provides flexibilty to add class and vendor specific
 *              requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 * Handles Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
uint_8 USB_Composite_Other_Requests (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;  
    INTERFACE_ARC_STRUCT_PTR intf_arc_ptr; 
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    uint_8 itf_num = 0xFF,count,index,offset = 0;
    uint_8 ep_num = 0;
    
    *data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;
    if(size == NULL)
    {
        return USBERR_GET_MEMORY_FAILED;
    }
    
    /* request is for an Interface */
    if(setup_packet->request_type & 0x01)
        itf_num = (uint_8)(setup_packet->index);
    /* request is for an Endpoint */
    else if(setup_packet->request_type & 0x02)
        ep_num = (uint_8)(setup_packet->index);
    
    
    /* Get device architecture */
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);
    for(count=0;count<dev_arc_ptr->cl_count;count++) 
    {
        dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count]; 
        if(dev_class_ptr->class_type == PHDC_COMP_CC)
            offset = (uint_8)(sizeof(dev_class_ptr->class_type) + dev_class_ptr->value[0]*(sizeof(USB_EP_STRUCT)+1));
        else
            offset = (uint_8)(sizeof(dev_class_ptr->class_type) + dev_class_ptr->value[0]*sizeof(USB_EP_STRUCT));
        intf_arc_ptr = (INTERFACE_ARC_STRUCT_PTR)&dev_class_ptr->value[offset];
        switch(dev_class_ptr->class_type)  
        {
#ifdef USE_HID_CLASS
            /* Call Hid other request */
            case HID_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_HID_Other_Requests(controller_ID,setup_packet,data,size); 
                }
            break;
#endif
#ifdef USE_AUDIO_CLASS   
            /* Call Audio other request */
            case AUDIO_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_Audio_Other_Requests(controller_ID,setup_packet,data,size);
                }
            break;
#endif
#ifdef USE_VIDEO_CLASS   
            /* Call Video other request */
            case VIDEO_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_Video_Other_Requests(controller_ID,setup_packet,data,size);
                }
            break;
#endif
#ifdef USE_CDC_CLASS    
            /* Call Cdc other request */ 
            case CDC_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_CDC_Other_Requests(controller_ID,setup_packet,data,size);
                }
                break;
#endif
#ifdef USE_MSD_CLASS     
            /* Call Msd other request */
            case MSD_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_MSC_Other_Requests(controller_ID,setup_packet,data,size);
                }
                break;
#endif
#ifdef USE_PHDC_CLASS
            /* Call Phdc other request */
            case PHDC_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_Phdc_Other_Requests(controller_ID,setup_packet,data,size); 
                }
                break;
#endif
#ifdef USE_DFU_CLASS
            /* Call Dfu other request */
            case DFU_COMP_CC:
                for(index = 0;index<intf_arc_ptr->interface_count;index++)
                {
                    if(itf_num == intf_arc_ptr->value[index] || ep_num != 0xFF)
                        status = USB_HID_Other_Requests(controller_ID,setup_packet,data,size);
                }
                break;
#endif
            default:
                break;
        }
        
    }
    return status;  
}

/* EOF */
