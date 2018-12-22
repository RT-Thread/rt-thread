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
 * @file usb_hid.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack HID layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_hid.h"    /* USB HID Class Header File */
#include "usb_devapi.h" /* USB device Header File */

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* HID endpoint info array */
static USB_CLASS_HID_ENDPOINT_DATA g_hid_endpoint_data;
/* HID Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_hid_class_callback=NULL;
/* HID Class Vendor Callback Function Pointer */
static USB_REQ_FUNC       g_vendor_req_callback=NULL;
/* HID Class requests Callback Function Pointer */
static USB_CLASS_SPECIFIC_HANDLER_FUNC g_param_callback = NULL;
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests(uint_8 controller_ID,
                          USB_SETUP_STRUCT * setup_packet,
                          uint_8_ptr *data,
                          USB_PACKET_SIZE *size);
#endif
static uint_8 USB_Map_Ep_To_Struct_Index(uint_8 controller_ID,
                                         uint_8 ep_num);

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
uint_8 g_class_request_params[2]; /* for get/set idle and protocol requests*/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
 /**************************************************************************//*!
 *
 * @name  USB_Map_Ep_To_Struct_Index
 *
 * @brief The funtion maps the endpoint number to the index of the endpoint
 *        data structure
 *
 * @param controller_ID     : Controller ID
 * @param ep_num            : Endpoint number
 *
 * @return index            : mapped index
 *
 ******************************************************************************
 * Returns the index of the endpoint info array for the particular endpoint
 * number
 *****************************************************************************/
static uint_8 USB_Map_Ep_To_Struct_Index (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 ep_num           /* Endpoint Number */
)
{
    uint_8 index = 0;

    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(controller_ID);

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < ep_desc_data->count; index++)
    {
        if(ep_desc_data->ep[index].ep_num == ep_num)
        {
            break;
        }
    }

    return index;

}

/**************************************************************************//*!
 *
 * @name  USB_Service_Hid
 *
 * @brief The function is a callback function of HID endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * This function is called from lower layer when data is transfer is completed
 * on HID endpoint (non control endpoint)
 *****************************************************************************/
void USB_Service_Hid (
    PTR_USB_DEV_EVENT_STRUCT event /* [IN] Pointer to USB Event Structure */
)
{
    uint_8 index;
    uint_8 producer, consumer;
    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(event->controller_ID);

     /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(event->controller_ID, event->ep_num);

    producer = g_hid_endpoint_data.ep[index].bin_producer;

    /* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
    if(event->errors == 0)
    {
        /* de-queue if the send is complete without an error */
        g_hid_endpoint_data.ep[index].bin_consumer++;
    }
    else
    {
        /* notify the application of the error */
        g_hid_class_callback(event->controller_ID, USB_APP_ERROR,
            (uint_8*)(&(event->errors)));
    }
    consumer = g_hid_endpoint_data.ep[index].bin_consumer;

    if(consumer != producer)
    {
        /*if bin is not empty */
        USB_CLASS_HID_QUEUE queue;
        /* send the next packet in queue */
        queue = g_hid_endpoint_data.ep[index].
            queue[consumer % MAX_QUEUE_ELEMS];

        (void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
            queue.app_buff, queue.size);
    }

    /* notify the app of the send complete */
    g_hid_class_callback(event->controller_ID, USB_APP_SEND_COMPLETE, 0);
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Hid_Event
 *
 * @brief The function initializes HID endpoint
 *
 * @param controller_ID     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * The funtion initializes the HID endpoints when Enumeration complete event is
 * received
 *****************************************************************************/
 void USB_Class_Hid_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */
)
{
    uint_8 index;

    if(event == USB_APP_ENUM_COMPLETE)
    {
        uint_8 index_num = 0;
        uint_8 count = 0,ep_count = 0;
        USB_ENDPOINTS *ep_desc_data;  
        
#ifdef COMPOSITE_DEV
        DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
        CLASS_ARC_STRUCT_PTR dev_class_ptr;   
        dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);    
        for(count = 0; count < dev_arc_ptr->cl_count; count++)
        {
            dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
            /* Initializes sub_classes */
            ep_count = dev_class_ptr->value[0];
            if(dev_class_ptr->class_type == 0x03/*HID_CC*/)
                break;
            index_num +=dev_class_ptr->value[0];
        }
        /* get the endpoints from the descriptor module */
        ep_desc_data = (USB_ENDPOINTS *)USB_Desc_Get_Endpoints(controller_ID); 
#else
        /* get the endpoints from the descriptor module */
        ep_desc_data = (USB_ENDPOINTS *)USB_Desc_Get_Endpoints(controller_ID); 
                    		    
		ep_count = ep_desc_data->count; 
#endif
		/* deinitialize all endpoints in case they were initialized */
		for(count=index_num;count<ep_count+index_num;count++) 
		{   
			USB_EP_STRUCT_PTR ep_struct_ptr= 
				(USB_EP_STRUCT_PTR) (&ep_desc_data->ep[count]);
			(void)_usb_device_deinit_endpoint(&controller_ID,
				ep_struct_ptr->ep_num, ep_struct_ptr->direction);  
		}

        /* intialize all non control endpoints */
        for(count=index_num;count<ep_count+index_num;count++)
        {
            USB_EP_STRUCT_PTR ep_struct=
                (USB_EP_STRUCT_PTR)&ep_desc_data->ep[count];

            (void)_usb_device_init_endpoint(&controller_ID, ep_struct->ep_num,
            		ep_struct->size, ep_struct->direction, ep_struct->type,
            		TRUE);

            /* register callback service for the endpoint */
            (void)_usb_device_register_service(controller_ID,
                                  (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                                                             USB_Service_Hid);


            /* set the EndPoint Status as Idle in the device layer */
            (void)_usb_device_set_status(&controller_ID,
                (uint_8)(USB_STATUS_ENDPOINT | HID_ENDPOINT |
                (ep_struct->direction << USB_COMPONENT_DIRECTION_SHIFT)),
                USB_STATUS_IDLE);
        }

    }
    else if((event == USB_APP_BUS_RESET) || (event == USB_APP_CONFIG_CHANGED))
    {
        /* clear producer and consumer on reset */
        for(index = 0; index < g_hid_endpoint_data.count; index++)
        {
            g_hid_endpoint_data.ep[index].bin_consumer = 0x00;
            g_hid_endpoint_data.ep[index].bin_producer = 0x00;
            g_hid_endpoint_data.ep[index].queue_num    = 0x00;
        }
    }

    if(g_hid_class_callback != NULL)
    {
        /* notify the application of the event */
        g_hid_class_callback(controller_ID, event, val);
    }

}

/**************************************************************************//*!
 *
 * @name  USB_Other_Requests
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
 * Handles HID Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests 
#else
uint_8 USB_HID_Other_Requests 
#endif
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /*[IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 index;
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    uint_8 rpt_buf[REPORT_SIZE];/* buffer to send in case of get report req */
    *((uint_32_ptr)rpt_buf) = 0;

    if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_CLASS)
    {
        /* class request so handle it here */
        /* index == 0 for get/set idle, index == 1 for get/set protocol */
        index = (uint_8)((setup_packet->request - 2) &
            USB_HID_REQUEST_TYPE_MASK);

        status = USB_OK;
        /* point to the data which comes after the setup packet */
        *data = ((uint_8*)setup_packet) + USB_SETUP_PKT_SIZE;
        *size = 0;
        /* handle the class request */
        switch(setup_packet->request)
        {
            case USB_HID_GET_REPORT_REQUEST :
                /*set the data pointer to the buffer to send */
                *data = &rpt_buf[0];
                if(*size > REPORT_SIZE) *size = REPORT_SIZE;
                break;

            case USB_HID_SET_REPORT_REQUEST :
                for(index = 0; index < REPORT_SIZE; index++)
                {   /* copy the data sent by host in the buffer */
                  rpt_buf[index] = *(*data + index);
                }
                break;

            case USB_HID_GET_IDLE_REQUEST :
                /* point to the current idle rate */
                *data = &g_class_request_params[index];
                *size = CLASS_REQ_DATA_SIZE;
                break;

            case USB_HID_SET_IDLE_REQUEST :
                /* set the idle rate sent by the host */
                g_class_request_params[index] =(uint_8)((setup_packet->value
                    & MSB_MASK) >> HIGH_BYTE_SHIFT);
                break;

            case USB_HID_GET_PROTOCOL_REQUEST :
                /* point to the current protocol code
                            0 = Boot Protocol
                            1 = Report Protocol*/
                *data = &g_class_request_params[index];
                *size = CLASS_REQ_DATA_SIZE;
                break;

            case USB_HID_SET_PROTOCOL_REQUEST :
                /* set the protocol sent by the host
                             0 = Boot Protocol
                             1 = Report Protocol*/
                g_class_request_params[index] = (uint_8)(setup_packet->value);
                break;
            default :
                break;
        }

        if(g_param_callback != NULL)
        {
            /* 
               handle callback if the application has supplied it
               set the size of the transfer from the setup packet 
            */
            *size = (USB_PACKET_SIZE)setup_packet->length; 

            /* notify the application of the class request.
               give control to the application */
            status = g_param_callback(setup_packet->request,/* request type */
                setup_packet->value,
                data,/* pointer to the data */
                size);/* size of the transfer */
        }

    }
    else if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_VENDOR)
    {
        /* vendor specific request  */
        if(g_vendor_req_callback != NULL)
        {
            status = g_vendor_req_callback(controller_ID, setup_packet,data,
                size);
        }
    }
    return status;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_HID_Init
 *
 * @brief   The funtion initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   hid_class_callback          : HID Class Callback
 * @param   vendor_req_callback         : Vendor Request Callback
 * @param   param_callback              : Class requests Callback
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the HID Class layer and layers it is dependent on
 *****************************************************************************/
uint_8 USB_Class_HID_Init (
    uint_8    controller_ID,                /* [IN] Controller ID */
    USB_CLASS_CALLBACK hid_class_callback,  /* [IN] HID Class Callback */
    USB_REQ_FUNC       vendor_req_callback, /* [IN] Vendor Request Callback */
    USB_CLASS_SPECIFIC_HANDLER_FUNC param_callback
                                        /* [ IN] HID Class requests Callback */
)
{
    uint_8 index,status = USB_OK;
    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(controller_ID);
    
#ifndef COMPOSITE_DEV
    /* Initialize the device layer*/
    status = _usb_device_init(controller_ID, NULL,
        (uint_8)(ep_desc_data->count+1), TRUE);
    if(status == USB_OK)
    {
        /* Initialize the generic class functions */
        status = USB_Class_Init(controller_ID,USB_Class_Hid_Event,
            USB_Other_Requests);

        if(status == USB_OK)
        {
#endif
            g_hid_endpoint_data.count = ep_desc_data->count;

            for(index = 0; index < ep_desc_data->count; index++)
            {
                g_hid_endpoint_data.ep[index].endpoint =
                    ep_desc_data->ep[index].ep_num;
                g_hid_endpoint_data.ep[index].type =
                    ep_desc_data->ep[index].type;
                g_hid_endpoint_data.ep[index].bin_consumer = 0x00;
                g_hid_endpoint_data.ep[index].bin_producer = 0x00;
            }

            /* save the HID class callback pointer */
            g_hid_class_callback = hid_class_callback;

            /* save the vendor request callback pointer */
            g_vendor_req_callback = vendor_req_callback;

            /* Save the callback to ask application for class specific params*/
            g_param_callback = param_callback;
#ifndef COMPOSITE_DEV
        }
    }
#endif
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_HID_DeInit
 *
 * @brief   The funtion de-initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function de-initializes the HID Class layer
 *****************************************************************************/
uint_8 USB_Class_HID_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status = USB_OK;
#ifdef COMPOSITE_DEV 
    UNUSED(controller_ID)
#endif  
    /* free the HID class callback pointer */
    g_hid_class_callback = NULL;
    
    /* free the vendor request callback pointer */
    g_vendor_req_callback = NULL;
    
    /* free the callback to ask application for class specific params*/
    g_param_callback = NULL;
    
#ifndef COMPOSITE_DEV
    /* Call common class deinit function */
    status = USB_Class_DeInit(controller_ID);
    
    if(status == USB_OK)
    /* Call device deinit function */
    	status = _usb_device_deinit();
#endif	
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_HID_Send_Data
 *
 * @brief This fucntion is used by Application to send data through HID class
 *
 * @param controller_ID     : Controller ID
 * @param ep_num            : Endpoint number
 * @param app_buff          : Buffer to send
 * @param size              : Length of the transfer
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 * This function is used by Application to send data through HID class
 *****************************************************************************/
uint_8 USB_Class_HID_Send_Data (
    uint_8 controller_ID,       /* [IN] Controller ID */
    uint_8 ep_num,              /* [IN] Endpoint Number */
    uint_8_ptr app_buff,        /* [IN] Buffer to Send */
    USB_PACKET_SIZE size        /* [IN] Length of the Transfer */
)
{
    uint_8 index;
    //volatile uint_8 producer, consumer;
    uint_8 producer, consumer;
    uint_8 status = USB_OK;

    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(controller_ID);

     /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(controller_ID, ep_num);

    producer = g_hid_endpoint_data.ep[index].bin_producer;
    consumer = g_hid_endpoint_data.ep[index].bin_consumer;

    if((uint_8)(producer - consumer) != (uint_8)(MAX_QUEUE_ELEMS))
    {
        /* the bin is not full*/

        uint_8 queue_num = (uint_8)(producer % MAX_QUEUE_ELEMS);

        /* queue the send request */
        /* put all send request parameters in the endpoint data structure */
        g_hid_endpoint_data.ep[index].queue[queue_num].controller_ID =
            controller_ID;
        g_hid_endpoint_data.ep[index].queue[queue_num].channel = ep_num;
        g_hid_endpoint_data.ep[index].queue[queue_num].app_buff = app_buff;
        g_hid_endpoint_data.ep[index].queue[queue_num].size = size;

        /* increment producer bin by 1*/
        g_hid_endpoint_data.ep[index].bin_producer++;
        producer++;

        if((uint_8)(producer - consumer) == (uint_8)1)
        {
            /* send the IO if there is only one element in the queue */
            status = USB_Class_Send_Data(controller_ID, ep_num, app_buff,size);
        }

    }
    else /* bin is full */
    {
        status = USBERR_DEVICE_BUSY;
    }
    return status;
}
