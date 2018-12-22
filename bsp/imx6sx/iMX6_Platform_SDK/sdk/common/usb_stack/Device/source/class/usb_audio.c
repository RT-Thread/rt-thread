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
 * @file usb_audio.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack Audio layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_audio.h"    	/* USB Audio Class Header File */
#include "usb_devapi.h"   	/* USB device Header File */
#include "usb_framework.h"  /* USB device Header File */

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Audio endpoint info array */
static USB_CLASS_AUDIO_ENDPOINT_DATA g_audio_endpoint_data;
/* Audio Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_audio_class_callback=NULL;
/* Audio Class Vendor Callback Function Pointer */
static USB_REQ_FUNC       g_vendor_req_callback=NULL;
/* Audio Class requests Callback Function Pointer */
static USB_CLASS_CALLBACK g_param_callback = NULL;
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
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef USE_FEEDBACK_ENDPOINT
	uint_32 feedback_data = 0;
	uint_32 gNrSamples = 0;
#endif

/*****************************************************************************
 * Local Functions
 *****************************************************************************/


/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Status_Interrupt
 *
 * @brief The funtion is callback function of Audio Status Interrupt endpoint
 *
 * @param event
 *
 * @return None
 *
 ****************************************************************************
 * This function is called in response to Status Interrupt Service
 ****************************************************************************/
void USB_Service_Audio_Status_Interrupt(PTR_USB_DEV_EVENT_STRUCT event)
{
#if IMPLEMENT_QUEUING
	uint_8 index;
	uint_8 producer, consumer;

	USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
	USB_Desc_Get_Endpoints(event->controller_ID);

	/* map the endpoint num to the index of the endpoint structure */

	for(index = 0; index < usb_ep_data->count; index++)
	{
		if(usb_ep_data->ep[index].ep_num == event->ep_num)
			break;
	}

	producer = g_audio_endpoint_data.ep[index].bin_producer;
	consumer = g_audio_endpoint_data.ep[index].bin_consumer;
    UNUSED(producer);
    
	/* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
	if (event->errors == 0)
	{
		/* de-queue if the send is complete without an error */
		if((MAX_QUEUE_ELEMS-1) == consumer)
		{
			g_audio_endpoint_data.ep[index].bin_consumer = 0;
		}
		else
		{
			g_audio_endpoint_data.ep[index].bin_consumer++;
		}
	}

	consumer = g_audio_endpoint_data.ep[index].bin_consumer;
	g_audio_endpoint_data.ep[index].queue_num--;

	if(0 == g_audio_endpoint_data.ep[index].queue_num)
	{
		/*if bin is not empty */
		USB_CLASS_AUDIO_QUEUE queue;
		/* send the next packet in queue */
		queue = g_audio_endpoint_data.ep[index].queue[consumer];

		(void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
				queue.app_buff, queue.size);
	}
#endif

	if(g_param_callback != NULL)
	{
		uint_8 event_type = USB_APP_SEND_COMPLETE;

		if(event->errors != 0)
		{
			event_type = USB_APP_ERROR;
		}
		g_param_callback(event->controller_ID, event_type,
				(uint_8*)(&(event->errors)));
	}
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Isochronous_IN
 *
 * @brief The funtion ic callback function of Audio Isochronous IN endpoint
 *
 * @param event
 *
 * @return None
 *
 ****************************************************************************
 * The function is called in response to Isochronous IN Service
 ******************************************************************************/
void USB_Service_Audio_Isochronous_IN(PTR_USB_DEV_EVENT_STRUCT event)
{

#if IMPLEMENT_QUEUING
    uint_8 index;
    uint_8 producer, consumer;
    APP_DATA_STRUCT iso_in_recv;

    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(event->controller_ID);
        
    iso_in_recv.data_ptr  = event->buffer_ptr;
    iso_in_recv.data_size = event->len;

	/* map the endpoint num to the index of the endpoint structure */

	for(index = 0; index < usb_ep_data->count; index++)
	{
		if(usb_ep_data->ep[index].ep_num ==event->ep_num)
			break;
	}


	producer = g_audio_endpoint_data.ep[index].bin_producer;
    UNUSED(producer);

	/* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
	if(event->errors == 0)
	{
		/* de-queue if the send is complete without an error */
		if ((MAX_QUEUE_ELEMS-1) == g_audio_endpoint_data.ep[index].bin_consumer)
		{
			g_audio_endpoint_data.ep[index].bin_consumer = 0;
		} else {
			g_audio_endpoint_data.ep[index].bin_consumer++;
		}
		g_audio_endpoint_data.ep[index].queue_num--;
	}

	consumer = g_audio_endpoint_data.ep[index].bin_consumer;

	if(0 != g_audio_endpoint_data.ep[index].queue_num)
	{
		/*if bin is not empty */
		USB_CLASS_AUDIO_QUEUE queue;
		/* send the next packet in queue */
		queue = g_audio_endpoint_data.ep[index].queue[consumer];

		(void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
				queue.app_buff, queue.size);
	}
#endif

	if(g_audio_class_callback != NULL)
	{
		uint_8 event_type = USB_APP_SEND_COMPLETE;

		if(event->errors != 0)
		{
			event_type = USB_APP_ERROR;
		}
		g_audio_class_callback(event->controller_ID, event_type,
				(uint_8*)(&iso_in_recv));
	}
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Isochronous_OUT
 *
 * @brief The funtion is callback function of Isochronous Out Endpoint
 *
 * @param event
 *
 * @return None
 *
 ****************************************************************************
 * The function is called in response to Isochronous OUT Service
 *****************************************************************************/
void USB_Service_Audio_Isochronous_OUT(PTR_USB_DEV_EVENT_STRUCT event)
{
	APP_DATA_STRUCT iso_out_recv;

	if(g_audio_class_callback != NULL)
	{

		if(event->errors != 0)
		{
			g_audio_class_callback(event->controller_ID, USB_APP_ERROR,
					(uint_8*)(&(event->errors)));
		}  else {
			iso_out_recv.data_ptr = event->buffer_ptr;
			iso_out_recv.data_size = event->len;
			g_audio_class_callback(event->controller_ID, USB_APP_DATA_RECEIVED,
					(uint_8*)(&(iso_out_recv)));

		}
	}
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Event
 *
 * @brief The funtion initializes Audio endpoint
 *
 * @param controller_ID     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * The funtion initializes the Audio endpoints when event of comleted enumeration is
 * received
 *****************************************************************************/
void USB_Class_Audio_Event (
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
             if(dev_class_ptr->class_type == 0x01/*AUDIO_CC*/)
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
         for(count=index_num; count<ep_count+index_num; count++) 
         {   
             USB_EP_STRUCT_PTR ep_struct_ptr= 
                 (USB_EP_STRUCT_PTR) (&ep_desc_data->ep[count]);
             (void)_usb_device_deinit_endpoint(&controller_ID,
                 ep_struct_ptr->ep_num, ep_struct_ptr->direction);
         }

         /* intialize all non control endpoints */
         for(count=index_num; count<ep_count+index_num; count++) 
         {
             USB_EP_STRUCT_PTR ep_struct=
                 (USB_EP_STRUCT_PTR)&ep_desc_data->ep[count];

             (void)_usb_device_init_endpoint(&controller_ID, ep_struct->ep_num,
                 ep_struct->size, ep_struct->direction, ep_struct->type, FALSE);

             /* register callback service for the endpoint */
             switch(ep_struct->type)
             {
                 case USB_INTERRUPT_PIPE:
                     (void)_usb_device_register_service(controller_ID,
                         (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                         USB_Service_Audio_Status_Interrupt);
                     break;
                 case USB_ISOCHRONOUS_PIPE:
                     if (ep_struct->direction == USB_RECV)
                     {
                         (void)_usb_device_register_service(controller_ID,
                             (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                             USB_Service_Audio_Isochronous_OUT);
                     }
                     else
                     {
                         (void)_usb_device_register_service(controller_ID,
                             (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                             USB_Service_Audio_Isochronous_IN);
                     }
                     break;
                 default:
                     break;
             }

             /* set the EndPoint Status as Idle in the device layer */
             (void)_usb_device_set_status(&controller_ID,
                 (uint_8)(USB_STATUS_ENDPOINT | 1|
                     (ep_struct->direction << USB_COMPONENT_DIRECTION_SHIFT)),
                     USB_STATUS_IDLE);
         }
     }
     else if(event == USB_APP_BUS_RESET)
     {
         /* clear producer and consumer on reset */
         for(index = 0; index < g_audio_endpoint_data.count; index++)
         {
             g_audio_endpoint_data.ep[index].bin_consumer = 0x00;
             g_audio_endpoint_data.ep[index].bin_producer = 0x00;
             g_audio_endpoint_data.ep[index].queue_num    = 0x00;
         }
     }

     if(g_audio_class_callback != NULL)
     {
         /* notify the event to the application */
         g_audio_class_callback(controller_ID, event, val);
     }
}

#if AUDIO_CLASS_2_0
/**************************************************************************
 *
 * @name: USB_Set_Cur_Audio_Clock
 *
 * @brief The function sets current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Set_Cur_Audio_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] interface */
    uint_8 control_selector,            /* [IN] control selector */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;

    switch(control_selector)
    {
        case CS_SAM_FREQ_CONTROL:
            status = USB_Desc_Set_Cur_Sampling_Frequency(controller_ID,interface,data, size);
            break;
        default:
            break;
    }
    return status;
}

/**************************************************************************
 *
 * @name: USB_Set_Min_Audio_Clock
 *
 * @brief The function sets current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Set_Min_Audio_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] interface */
    uint_8 control_selector,            /* [IN] control selector */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;

    switch(control_selector)
    {
        case CS_SAM_FREQ_CONTROL:
            status = USB_Desc_Set_Min_Sampling_Frequency(controller_ID,interface,data, size);
            break;
        default:
            break;
    }
    return status;
}

/**************************************************************************
 *
 * @name: USB_Set_Max_Audio_Clock
 *
 * @brief The function sets current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Set_Max_Audio_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] interface */
    uint_8 control_selector,            /* [IN] control selector */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;

    switch(control_selector)
    {
        case CS_SAM_FREQ_CONTROL:
            status = USB_Desc_Set_Max_Sampling_Frequency(controller_ID,interface,data, size);
            break;
        default:
            break;
    }
    return status;
}

/**************************************************************************
 *
 * @name: USB_Set_Res_Audio_Clock
 *
 * @brief The function sets current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Set_Res_Audio_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] interface */
    uint_8 control_selector,            /* [IN] control selector */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;

    switch(control_selector)
    {
        case CS_SAM_FREQ_CONTROL:
            status = USB_Desc_Set_Res_Sampling_Frequency(controller_ID,interface,data, size);
            break;
        default:
            break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Cur_Audio_Clock
 *
 * @brief The function gets Current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Control_Clock function
 *****************************************************************************/

static uint_8 USB_Get_Cur_Audio_Clock(
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 interface,                   /* [IN] interface */
        uint_8 control_selector,            /* [IN] control selector */
        uint_8_ptr *data,                   /* [OUT] Pointer to Data */
        USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    /* check control selector */
    switch(control_selector)
    {
    case CS_SAM_FREQ_CONTROL:
        status = USB_Desc_Get_Cur_Sampling_Frequency(controller_ID,interface,data,size);
        break;
    case CS_CLOCK_VALID_CONTROL:
        status = USB_Desc_Get_Cur_Clock_Validity(controller_ID,interface,data,size);
        break;
    default:
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Min_Audio_Clock
 *
 * @brief The function gets Min attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Get_Min_Audio_Clock(
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 interface,                   /* [IN] interface */
        uint_8 control_selector,            /* [IN] control selector */
        uint_8_ptr *data,                   /* [OUT] Pointer to Data */
        USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    switch(control_selector)
    {
    case CS_SAM_FREQ_CONTROL:
        status = USB_Desc_Get_Min_Sampling_Frequency(controller_ID,interface,data,size);
        break;
    default:
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Max_Audio_Clock
 *
 * @brief The function gets Max attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Control_Clock function
 *****************************************************************************/
static uint_8 USB_Get_Max_Audio_Clock(
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 interface,                   /* [IN] interface */
        uint_8 control_selector,            /* [IN] control selector */
        uint_8_ptr *data,                   /* [OUT] Pointer to Data */
        USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    switch(control_selector)
    {
    case CS_SAM_FREQ_CONTROL:
        status = USB_Desc_Get_Max_Sampling_Frequency(controller_ID,interface,data,size);
        break;
    default:
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Res_Audio_Clock
 *
 * @brief The function gets Resolution attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Control_Clock function
 *****************************************************************************/

static uint_8 USB_Get_Res_Audio_Clock(
        uint_8 controller_ID,               /* [IN] Controller ID */
        uint_8 interface,                   /* [IN] interface */
        uint_8 control_selector,            /* [IN] control selector */
        uint_8_ptr *data,                   /* [OUT] Pointer to Data */
        USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    switch(control_selector)
    {
    case CS_SAM_FREQ_CONTROL:
        status = USB_Desc_Get_Res_Sampling_Frequency(controller_ID,interface,data,size);
        break;

    default:
        break;
    }
    return status;
}
#endif /* AUDIO_CLASS_2_0 */

/**************************************************************************//*!
 *
 * @name: USB_Set_Cur_Audio_Feature_Unit
 *
 * @brief The function sets current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Set_Cur_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	switch(control_selector)
	{
	case MUTE_CONTROL:
		status = USB_Desc_Set_Cur_Mute(controller_ID,interface,data, size);
		break;
	case VOLUME_CONTROL:
		status = USB_Desc_Set_Cur_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Set_Cur_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Set_Cur_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Set_Cur_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status=USB_Desc_Set_Cur_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case AUTOMATIC_GAIN_CONTROL:
		status = USB_Desc_Set_Cur_Automatic_Gain(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Set_Cur_Delay(controller_ID,interface,data,size);
		break;
	case BASS_BOOST_CONTROL:
		status = USB_Desc_Set_Cur_Bass_Boost(controller_ID,interface,data,size);
		break;
	case LOUDNESS_CONTROL:
		status = USB_Desc_Set_Cur_Loudness(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Set_Min_Audio_Feature_Unit
 *
 * @brief The function sets Min attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Set_Min_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Set_Min_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Set_Min_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Set_Min_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Set_Min_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Set_Min_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Set_Min_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Set_Max_Audio_Feature_Unit
 *
 * @brief The function sets Max attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Set_Max_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Set_Max_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Set_Max_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Set_Max_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Set_Max_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status =USB_Desc_Set_Max_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Set_Max_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Set_Res_Audio_Feature_Unit
 *
 * @brief The function sets Resolution attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Set_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Set_Res_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Set_Res_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Set_Res_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Set_Res_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Set_Res_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Set_Res_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Set_Res_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Cur_Audio_Feature_Unit
 *
 * @brief The function gets Current attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Feature_Unit function
 *****************************************************************************/

static uint_8 USB_Get_Cur_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	/* check control selector */
	switch(control_selector)
	{
	case MUTE_CONTROL:
		status = USB_Desc_Get_Cur_Mute(controller_ID,interface,data,size);
		break;
	case VOLUME_CONTROL:
		status = USB_Desc_Get_Cur_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Get_Cur_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Get_Cur_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Get_Cur_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Get_Cur_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case AUTOMATIC_GAIN_CONTROL:
		status = USB_Desc_Get_Cur_Automatic_Gain(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Get_Cur_Delay(controller_ID,interface,data,size);
		break;
	case BASS_BOOST_CONTROL:
		status = USB_Desc_Get_Cur_Bass_Boost(controller_ID,interface,data,size);
		break;
	case LOUDNESS_CONTROL:
		status = USB_Desc_Get_Cur_Loudness(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Min_Audio_Feature_Unit
 *
 * @brief The function gets Min attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Get_Min_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Get_Min_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Get_Min_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Get_Min_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Get_Min_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Get_Min_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Get_Min_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Max_Audio_Feature_Unit
 *
 * @brief The function gets Max attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Feature_Unit function
 *****************************************************************************/
static uint_8 USB_Get_Max_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Get_Max_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Get_Max_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Get_Max_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Get_Max_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Get_Max_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status = USB_Desc_Get_Max_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Res_Audio_Feature_Unit
 *
 * @brief The function gets Resolution attributes of Feature Unit
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface number
 * @param control_selector  : Control Selector of Request
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called by USB_Audio_Get_Feature_Unit function
 *****************************************************************************/

static uint_8 USB_Get_Res_Audio_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 interface,                   /* [IN] interface */
		uint_8 control_selector,            /* [IN] control selector */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	switch(control_selector)
	{
	case VOLUME_CONTROL:
		status = USB_Desc_Get_Res_Volume(controller_ID,interface,data,size);
		break;
	case BASS_CONTROL:
		status = USB_Desc_Get_Res_Bass(controller_ID,interface,data,size);
		break;
	case MID_CONTROL:
		status = USB_Desc_Get_Res_Mid(controller_ID,interface,data,size);
		break;
	case TREBLE_CONTROL:
		status = USB_Desc_Get_Res_Treble(controller_ID,interface,data,size);
		break;
	case GRAPHIC_EQUALIZER_CONTROL:
		status = USB_Desc_Get_Res_Graphic_Equalizer(controller_ID,interface,data,size);
		break;
	case DELAY_CONTROL:
		status=USB_Desc_Get_Res_Delay(controller_ID,interface,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Audio_Set_Control_Terminal
 *
 * @brief The function sets Copy protect level for I/O Terminal
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This funtion is called in USB_Set_Request_Interface function
 *****************************************************************************/
static uint_8 USB_Audio_Set_Control_Terminal(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	switch(setup_packet -> request)
	{
	/*Copy Protect Control only supports the CUR attribute! */
	case SET_CUR:
		if((setup_packet->value >>8) == COPY_PROTECT_CONTROL )
		{
			status = USB_Desc_Set_Copy_Protect(controller_ID,(uint_8)setup_packet->index,data,size);
		}
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Audio_Get_Control_Terminal
 *
 * @brief The function gets Copy protect level for I/O Terminal
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This funtion is called in USB_Get_Request_Interface function
 *****************************************************************************/

static uint_8 USB_Audio_Get_Control_Terminal(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	switch(setup_packet -> request)
	{
	/* Copy Protect Control only supports the CUR attribute!*/
	case GET_CUR:
		if((setup_packet ->value >>8) == COPY_PROTECT_CONTROL )
		{
			status = USB_Desc_Get_Copy_Protect(controller_ID,(uint_8)setup_packet->index,data,size);
		}
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Audio_Set_Feature_Unit
 *
 * @brief The function sets Feature Unit requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This funtion is called in Set_Request_Interface function
 *****************************************************************************/
static uint_8 USB_Audio_Set_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 interface, control_selector;
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	/* get current interface */
	interface = (uint_8)setup_packet->index;
	/* get control selector */
	control_selector = (uint_8)(setup_packet->value>>8);

	/* Select SET request Control Feature Unit Module */
	switch(setup_packet->request)
	{
	case SET_CUR:
		/*Set current attributes of Feature Unit*/
		status = USB_Set_Cur_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case SET_MIN:
		/*Set Min attributes of Feature Unit*/
		status = USB_Set_Min_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case SET_MAX:
		/*Set Max attributes of Feature Unit*/
		status = USB_Set_Max_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case SET_RES:
		/*Set Resolution attributes of Feature Unit*/
		status = USB_Set_Res_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	default:
		break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Audio_Get_Feature_Unit
 *
 * @brief The function gets Feature Unit requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This funtion is called in the Get_Request_Interface function
 *****************************************************************************/
static uint_8 USB_Audio_Get_Feature_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 interface, control_selector;
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	interface = (uint_8)setup_packet->index;
	control_selector = (uint_8)(setup_packet->value>>8);
	/* Select SET request Control Feature Unit Module */
	switch(setup_packet->request)
	{
	case GET_CUR:
		status = USB_Get_Cur_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case GET_MIN:
		status = USB_Get_Min_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case GET_MAX:
		status = USB_Get_Max_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	case GET_RES:
		status = USB_Get_Res_Audio_Feature_Unit(controller_ID,interface,control_selector,data,size);
		break;
	default:
		break;
	}
    UNUSED(status);
	return USB_OK;
}

#if AUDIO_CLASS_2_0
/**************************************************************************//*!
 *
 * @name: USB_Audio_Set_Control_Clock
 *
 * @brief The function sets Clock requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called in Set_Request_Interface function
 *****************************************************************************/
static uint_8 USB_Audio_Set_Control_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 interface, control_selector;
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    /* get current interface */
    interface = (uint_8)setup_packet->index;
    /* get control selector */
    control_selector = (uint_8)(setup_packet->value>>8);

    /* Select SET request Control Clock Control Module */
    switch(setup_packet->request)
    {
        case SET_CUR:
            /*Set current attributes for Clock Control*/
            status = USB_Set_Cur_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case SET_MIN:
            /*Set Min attributes of Clock Control */
            status = USB_Set_Min_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case SET_MAX:
            /*Set Max attributes of Clock Control */
            status = USB_Set_Max_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case SET_RES:
            /*Set Resolution attributes of Clock Control */
            status = USB_Set_Res_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        default:
            break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Audio_Get_Control_Clock
 *
 * @brief The function gets Clock requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This function is called in the Get_Request_Interface function
 *****************************************************************************/
static uint_8 USB_Audio_Get_Control_Clock(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 interface, control_selector;
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    interface = (uint_8)setup_packet->index;
    control_selector = (uint_8)(setup_packet->value>>8);
    /* Select GET request Control Feature Unit Module */
    switch(setup_packet->request)
    {
        case GET_CUR:
            status = USB_Get_Cur_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case GET_MIN:
            status = USB_Get_Min_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case GET_MAX:
            status = USB_Get_Max_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        case GET_RES:
            status = USB_Get_Res_Audio_Clock(controller_ID,interface,control_selector,data,size);
            break;
        default:
            break;
    }
    return USB_OK;
}
#endif /* AUDIO_CLASS_2_0 */

/**************************************************************************//*!
 *
 * @name: USB_Set_Request_Interface
 *
 * @brief This function is called in response to Set Interface Requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * The funtion set Feature unit and Terminal request. It is called in
 * USB_Other_Request function
 *****************************************************************************/
static uint_8 USB_Set_Request_Interface(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [IN] Pointer to Data */
    USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
    uint_8 i;
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    USB_AUDIO_UNITS *entity_desc_data;
    USB_UT_STRUCT_PTR ut_struct;

    *size = 0;
    /* get the I/O Interface and Feature  from the descriptor module */
    entity_desc_data = (USB_AUDIO_UNITS *)USB_Desc_Get_Audio_Entities(controller_ID);

    for(i=0; i<AUDIO_UNIT_COUNT; i++)
    {
        ut_struct=(USB_UT_STRUCT_PTR)&(entity_desc_data->et[i]);
        /* wIndex H byte is Entity ID */
        if((setup_packet->index>>8) == ut_struct->unit_id)
        {
            switch(ut_struct->type)
            {
#if AUDIO_CLASS_2_0
                case AUDIO_CONTROL_CLOCK_SOURCE:
                    status = USB_Audio_Set_Control_Clock(controller_ID,setup_packet,data,size);
                    break;
#endif /* AUDIO_CLASS_2_0 */
                case AUDIO_CONTROL_INPUT_TERMINAL:
                    break;
                case AUDIO_CONTROL_FEATURE_UNIT:
                    /* Select SET request Control Feature Unit Module */
                    status = USB_Audio_Set_Feature_Unit(controller_ID,setup_packet,data,size);
                    break;
                case AUDIO_CONTROL_OUTPUT_TERMINAL:
                    /* Select SET request Output Terminal Module */
                    status = USB_Audio_Set_Control_Terminal(controller_ID,setup_packet,data,size);
                    break;
                default:
                    break;
            }
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Request_Interface
 *
 * @brief This function is called in response to Get Interface Requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * The funtion Get Feature unit and Terminal requests. It is called in
 * USB_Other_Request function
 *****************************************************************************/

static uint_8 USB_Get_Request_Interface(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 i;
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    USB_AUDIO_UNITS *entity_desc_data;
    USB_UT_STRUCT_PTR ut_struct;

    /* get the I/O Interface and Feature  from the descriptor module */
    entity_desc_data = (USB_AUDIO_UNITS *)USB_Desc_Get_Audio_Entities(controller_ID);

    for(i=0;i<AUDIO_UNIT_COUNT; i++)
    {
        ut_struct=(USB_UT_STRUCT_PTR)&(entity_desc_data->et[i]);
        if((setup_packet->index >>8) == ut_struct->unit_id)
        {
            switch(ut_struct->type)
            {
#if AUDIO_CLASS_2_0
                case AUDIO_CONTROL_CLOCK_SOURCE:
                    status = USB_Audio_Get_Control_Clock(controller_ID,setup_packet,data,size);
                    break;
#endif /* AUDIO_CLASS_2_0 */
                case AUDIO_CONTROL_INPUT_TERMINAL:
                    /*Select SET Request Control Input Terminal Module */
                    status = USB_Audio_Get_Control_Terminal(controller_ID,setup_packet,data,size);
                    break;
                case AUDIO_CONTROL_FEATURE_UNIT:
                    /* Select SET request Control Feature Unit Module */
                    status = USB_Audio_Get_Feature_Unit(controller_ID,setup_packet,data,size);
                    break;

                default:
                    break;
            }
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Set_Request_Endpoint
 *
 * @brief This function is called in response to Set Endpoint Requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 ** This funtion is called by USB_Other_Request function
 *****************************************************************************/
static uint_8 USB_Set_Request_Endpoint
(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [IN] Pointer to Data */
		USB_PACKET_SIZE *size               /* [IN] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	uint_8 interface;
	uint_8 control_selector;
	uint_16 offset;
	/* get current interface */
	interface = (uint_8)setup_packet->index;
	/* get control selector */
	control_selector = (uint_8)(setup_packet->value>>8);

	switch(setup_packet->request)
	{
	    case SET_CUR:
	    {
	        *size = 0;
	        switch(control_selector)
	        {
#if !AUDIO_CLASS_2_0
	            /*
	             * Request Valid only in Audio 1.0, in Audio 2.0 it was moved 
	             * into Interface Requests
	             */
	            case SAMPLING_FREQ_CONTROL:
	                status = USB_Desc_Set_Cur_Sampling_Frequency(controller_ID,interface,data,size);
	                break;
#endif /* AUDIO_CLASS_2_0 */
	            case PITCH_CONTROL:
	                status = USB_Desc_Set_Cur_Pitch(controller_ID,interface,data,size);
	                break;
	            default:
	                break;
	        }
	    }
	    break;

	    case SET_MIN:
	    {
	        *size = 0;
	        switch(control_selector)
	        {
#if !AUDIO_CLASS_2_0
	            case SAMPLING_FREQ_CONTROL:
	                status = USB_Desc_Set_Min_Sampling_Frequency(controller_ID,interface,data,size);
	                break;
#endif /* AUDIO_CLASS_2_0 */	                
	            default:
	                break;
	        }
	    }
	    break;
	    
	    case SET_MAX:
	    {
	        *size = 0;
	        switch(control_selector)
	        {
#if !AUDIO_CLASS_2_0
	            case SAMPLING_FREQ_CONTROL:
	                status = USB_Desc_Set_Max_Sampling_Frequency(controller_ID,interface,data,size);
	                break;
#endif /* AUDIO_CLASS_2_0 */
	            default:
	                break;
	        }
	    }
	    break;

	    case SET_RES:
	    {
	        *size = 0;
	        switch(control_selector)
	        {
#if !AUDIO_CLASS_2_0
	            case SAMPLING_FREQ_CONTROL:
	                status = USB_Desc_Set_Res_Sampling_Frequency(controller_ID,interface,data,size);
	                break;
#endif /* AUDIO_CLASS_2_0 */
	            default:
	                break;
	        }
	    }
	    break;
	    case SET_MEM:
	        *size = setup_packet->length;
	        offset=setup_packet->value;
	        status = USB_Desc_Set_Mem_Endpoint(controller_ID,offset,interface,data,size);
	        break;
	    default:
	        break;
	}
	return status;
}

/**************************************************************************//*!
 *
 * @name: USB_Get_Request_Endpoint
 *
 * @brief This function is called in response to Get Endpoint Requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Pointer to setup packet
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 *
 ******************************************************************************
 * This funtion is called by USB_Other_Request function
 *****************************************************************************/
static uint_8 USB_Get_Request_Endpoint
(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	uint_8 interface;
	uint_8 control_selector;
	uint_16 offset;

	/* get current interface */
	interface = (uint_8)setup_packet->index;
	/* get control selector */
	control_selector = (uint_8)(setup_packet->value >>8);

	switch(setup_packet->request)
	{
	case  GET_CUR:
		switch(control_selector)
		{
		case SAMPLING_FREQ_CONTROL:
			status = USB_Desc_Get_Cur_Sampling_Frequency(controller_ID,interface,data,size);
			break;
		case PITCH_CONTROL:
			status = USB_Desc_Get_Cur_Pitch(controller_ID,interface,data,size);
			break;
		default:
			break;
		}
		break;
		case GET_MIN:
			switch(control_selector)
			{
			case SAMPLING_FREQ_CONTROL:
				status = USB_Desc_Get_Min_Sampling_Frequency(controller_ID,interface,data,size);
				break;
			default:
				break;
			}
			break;
			case GET_MAX:
				switch(control_selector)
				{
				case SAMPLING_FREQ_CONTROL:
					status = USB_Desc_Get_Max_Sampling_Frequency(controller_ID,interface,data,size);
					break;
				default:
					break;
				}
				break;
				case GET_RES:
					switch(control_selector)
					{
					case SAMPLING_FREQ_CONTROL:
						status = USB_Desc_Get_Res_Sampling_Frequency(controller_ID,interface,data,size);
						break;
					default:
						break;
					}
					break;
					case GET_MEM:
						*size = setup_packet->length;
						offset=setup_packet->value;
						status = USB_Desc_Get_Mem_Endpoint(controller_ID,offset,interface,data,size);
						break;
					default:
						break;
	}
	return status;
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
 * Handles Audio Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests 
#else 
uint_8 USB_Audio_Other_Requests
#endif
(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /*[IN] Setup packet received */
		uint_8_ptr *data,                   /* [OUT] Data to be send back */
		USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    /* point to the data which comes after the setup packet */
    *data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;
    if (size == NULL)				
    {
        return USBERR_GET_MEMORY_FAILED;	
    }
    switch(setup_packet->request_type)
    {
        /* Set I/O Terminal and Feature Unit */
        case SET_REQUEST_ITF:
            status = USB_Set_Request_Interface(controller_ID,setup_packet,data,size);
            break;
            /*Get I/O Terminal and Feature Unit */
        case GET_REQUEST_ITF:
            status = USB_Get_Request_Interface(controller_ID,setup_packet,data,size);
            break;
            /* Set Endpoint Request */
        case SET_REQUEST_EP:
            status = USB_Set_Request_Endpoint(controller_ID,setup_packet,data,size);
            break;
            /* Get Endpoint Request */
        case GET_REQUEST_EP:
            status = USB_Get_Request_Endpoint(controller_ID,setup_packet,data,size);
            break;
        default:
            break;
    } /* end of switch */
    return status;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Init
 *
 * @brief   The funtion initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   audio_class_callback        : Audio Class Callback
 * @param   vendor_req_callback         : Vendor Request Callback
 * @param   param_callback              : Class requests Callback
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the Audio Class layer and layers it is dependent on
 *****************************************************************************/
uint_8 USB_Class_Audio_Init (
		uint_8    controller_ID,                  /* [IN] Controller ID */
		USB_CLASS_CALLBACK audio_class_callback,  /* [IN] Audio Class Callback */
		USB_REQ_FUNC       vendor_req_callback,   /* [IN] Vendor Request Callback */
		USB_CLASS_CALLBACK param_callback         /* [ IN] Audio Class requests Callback */
)
{
	uint_8 index;
    uint_8 status = USB_OK;
	USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
	USB_Desc_Get_Endpoints(controller_ID);

#ifndef COMPOSITE_DEV
	/* Initialize the device layer*/
    status = _usb_device_init(controller_ID, NULL,
			(uint_8)(ep_desc_data->count+1), TRUE);
	if(status == USB_OK)
	{
		/* Initialize the generic class functions */
		status = USB_Class_Init(controller_ID,USB_Class_Audio_Event,
				USB_Other_Requests);

		if(status == USB_OK)
		{
#endif
			g_audio_endpoint_data.count = ep_desc_data->count;

			for(index = 0; index < ep_desc_data->count; index++)
			{
				g_audio_endpoint_data.ep[index].endpoint = ep_desc_data->ep[index].ep_num;
				g_audio_endpoint_data.ep[index].type = ep_desc_data->ep[index].type;
				g_audio_endpoint_data.ep[index].bin_consumer = 0x00;
				g_audio_endpoint_data.ep[index].bin_producer = 0x00;
				g_audio_endpoint_data.ep[index].queue_num    = 0x00;
			}

			/* save the Audio class callback pointer */
			g_audio_class_callback = audio_class_callback;

			/* save the vendor request callback pointer */
			g_vendor_req_callback = vendor_req_callback;
            
            UNUSED(g_vendor_req_callback);

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
 * @name  USB_Class_Audio_DeInit
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
 *This function de-initializes the Audio Class layer
 *****************************************************************************/
uint_8 USB_Class_Audio_DeInit
(
		uint_8 controller_ID              /* [IN] Controller ID */
)
{
    uint_8 status = USB_OK;
#ifdef COMPOSITE_DEV
    UNUSED(controller_ID)
#endif
	/* free the Audio class callback pointer */
	g_audio_class_callback = NULL;

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
 * @name  USB_Class_Audio_Send_Data
 *
 * @brief This fucntion is used by Application to send data through Audio class
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
 * This fucntion is used by Application to send data through Audio class
 *****************************************************************************/
uint_8 USB_Class_Audio_Send_Data (
		uint_8 controller_ID,       /* [IN] Controller ID */
		uint_8 ep_num,              /* [IN] Endpoint Number */
		uint_8_ptr app_buff,        /* [IN] Buffer to Send */
		USB_PACKET_SIZE size        /* [IN] Length of the Transfer */
)
{
	uint_8 status = USB_OK;
	PTR_USB_CLASS_AUDIO_QUEUE queue_tmp;

#if IMPLEMENT_QUEUING
	uint_8 index;
	uint_8 producer, queue_num;

	USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
	USB_Desc_Get_Endpoints(controller_ID);

	/* map the endpoint num to the index of the endpoint structure */

	for(index = 0; index < usb_ep_data->count; index++)
	{
		if(usb_ep_data->ep[index].ep_num == ep_num)
			break;
	}

	producer = g_audio_endpoint_data.ep[index].bin_producer;
	queue_num = g_audio_endpoint_data.ep[index].queue_num;
    
    UNUSED(producer);

	if(MAX_QUEUE_ELEMS != queue_num)
	{
		/* the bin is not full*/
		/* put all send request parameters in the endpoint data structure */
		queue_tmp = &(g_audio_endpoint_data.ep[index].queue[producer]);
		queue_tmp->controller_ID  = controller_ID;
		queue_tmp->channel        = ep_num;
		queue_tmp->app_buff       = app_buff;
		queue_tmp->size           = size;

		/* increment producer bin by 1*/
		if (producer == (MAX_QUEUE_ELEMS - 1))
		{
			g_audio_endpoint_data.ep[index].bin_producer = 0;
		}
		else
		{
			g_audio_endpoint_data.ep[index].bin_producer++;
		}
		g_audio_endpoint_data.ep[index].queue_num++;

		if(g_audio_endpoint_data.ep[index].queue_num == 1)
		{
#endif
			status = USB_Class_Send_Data(controller_ID, ep_num, app_buff,size);
#if IMPLEMENT_QUEUING
		}
	}
	else /* bin is full */
	{
		status = USBERR_DEVICE_BUSY;
	}
#endif
	return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Recv_Data
 *
 * @brief This function receives Data from Host.
 *
 * @param controller_ID     : Controller ID
 * @param ep_num            : Endpoint number
 * @param app_buff          : Buffer to send
 * @param size              : Length of the transfer
 *
 * @return status
 *         USB_OK         : When Successfull
 *         Others         : Errors
 ****************************************************************************
 * This function called bye USB_App_Callback function
 *****************************************************************************/
uint_8 USB_Class_Audio_Recv_Data
(
		uint_8 controller_ID,       /* [IN] Controller ID */
		uint_8 ep_num,              /* [IN] Endpoint Number */
		uint_8_ptr app_buff,        /* [IN] Buffer to Send */
		USB_PACKET_SIZE size        /* [IN] Length of the Transfer */
)
{
	uint_8 status;


	status = _usb_device_recv_data(&controller_ID,ep_num,app_buff,size);

	return status;

}
