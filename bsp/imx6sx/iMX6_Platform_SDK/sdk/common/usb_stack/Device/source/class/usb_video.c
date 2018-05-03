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
 * @file usb_video.c
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains USB stack Video layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_video.h"    		/* USB Video Class Header File */
#include "usb_devapi.h"   		/* USB device Header File */
#include "usb_framework.h"		/* USB device Header File */

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Video endpoint info array */
static USB_CLASS_VIDEO_ENDPOINT_DATA g_video_endpoint_data;
/* Video Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_video_class_callback=NULL;
/* Video Class Vendor Callback Function Pointer */
static USB_REQ_FUNC       g_vendor_req_callback=NULL;
/* Video Class requests Callback Function Pointer */
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
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Service_Video_Isochronous
 *
 * @brief The funtion ic callback function of Video Isochronous IN endpoint 
 *
 * @param event
 *
 * @return None       
 *
 ****************************************************************************
 * The function is called in response to Isochronous IN Service  
 ******************************************************************************/
void USB_Service_Video_Isochronous(PTR_USB_DEV_EVENT_STRUCT event)
{

#if IMPLEMENT_QUEUING
	uint_8 index;
	uint_8 producer, consumer;
	/*Body*/

	USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        		USB_Desc_Get_Endpoints(event->controller_ID);

	/* map the endpoint num to the index of the endpoint structure */
	for(index = 0; index < usb_ep_data->count; index++) 
	{
		if(usb_ep_data->ep[index].ep_num ==event->ep_num)
			break;
	}/*EndFor*/

	producer = g_video_endpoint_data.ep[index].bin_producer;	  
	/* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
	if(event->errors == 0)
	{
		/* de-queue if the send is complete without an error */
		if ((MAX_QUEUE_ELEMS-1) == g_video_endpoint_data.ep[index].bin_consumer)
		{
			g_video_endpoint_data.ep[index].bin_consumer = 0;
		} else {
			g_video_endpoint_data.ep[index].bin_consumer++;
		}/*EndIf*/
		g_video_endpoint_data.ep[index].queue_num--;
	}/*EndIf*/

	consumer = g_video_endpoint_data.ep[index].bin_consumer;

	if(0 != g_video_endpoint_data.ep[index].queue_num)
	{
		/*if bin is not empty */
		USB_CLASS_VIDEO_QUEUE queue;
		/* send the next packet in queue */
		queue = g_video_endpoint_data.ep[index].queue[consumer];

		(void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
				queue.app_buff, queue.size);
	}/*EndIf*/
#endif    

	if(g_video_class_callback != NULL)
	{
		uint_8 event_type = USB_APP_SEND_COMPLETE;

		if(event->errors != 0)
		{
			event_type = USB_APP_ERROR;
		}/*EndIf*/
		g_video_class_callback(event->controller_ID, event_type,
				(uint_8*)(&(event->errors)));
	}/*EndIf*/
}/*EndBody*/

/**************************************************************************//*!
 *
 * @name  USB_Class_Video_Event
 *
 * @brief The funtion initializes Video endpoint
 *
 * @param controller_ID     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * The funtion initializes the Video endpoints when event of comleted enumeration is
 * received
 *****************************************************************************/
 void USB_Class_Video_Event (
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
            if(dev_class_ptr->class_type == 0x0e/*VIDEO_CC*/)
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
          		ep_struct->size, ep_struct->direction, ep_struct->type,
          		TRUE);

          /* register callback service for the endpoint */
          switch(ep_struct->type)
          {
            case USB_INTERRUPT_PIPE:
                break;
            case USB_ISOCHRONOUS_PIPE:
                if(ep_struct->direction == USB_SEND)
                {
                (void)_usb_device_register_service(controller_ID,
                        (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                        USB_Service_Video_Isochronous);
                }
                break;
            default:
                break;
          }

          /* set the EndPoint Status as Idle in the device layer */
          (void)_usb_device_set_status(&controller_ID,
                (uint_8)(USB_STATUS_ENDPOINT | VIDEO_ENDPOINT |
              (ep_struct->direction << USB_COMPONENT_DIRECTION_SHIFT)),
              USB_STATUS_IDLE);
      }

    }
    else if(event == USB_APP_BUS_RESET)
    {
        /* clear producer and consumer on reset */
        for(index = 0; index < g_video_endpoint_data.count; index++)
        {
            g_video_endpoint_data.ep[index].bin_consumer = 0x00;
            g_video_endpoint_data.ep[index].bin_producer = 0x00;
            g_video_endpoint_data.ep[index].queue_num    = 0x00;
        }
    }

    if(g_video_class_callback != NULL)
    {
        /* notify the event to the application */
        g_video_class_callback(controller_ID, event, val);
    }
}

static uint_8 USB_Video_Get_Cur_Control_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){
	case VC_VIDEO_POWER_MODE_CONTROL:
		status=USB_Desc_Get_Cur_Power_Mode(controller_ID,data,size);
		break;

	case VC_REQUEST_ERROR_CODE_CONTROL:
		status=USB_Desc_Get_Cur_Error_Code(controller_ID,data,size); 
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Set_Cur_Control_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){
	case VC_VIDEO_POWER_MODE_CONTROL:
		status=USB_Desc_Set_Cur_Power_Mode(controller_ID,data,size);  
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Info_Control_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*EndBody*/
	switch(control_selector){
	case VC_VIDEO_POWER_MODE_CONTROL:
		status=USB_Desc_Get_Info_Power_Mode(controller_ID,data,size);
		break;

	case VC_REQUEST_ERROR_CODE_CONTROL:
		status=USB_Desc_Get_Info_Error_Code(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSitch*/
	return status;
}/*EndBody*/

/**************************************************************************//*!
 *
 * @name: USB_Video_Get_Control_Interface_Requests 
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
static uint_8 USB_Video_Get_Control_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 bRequest,      
		uint_8 control_selector,
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(bRequest)
	{
	case GET_CUR:
		status=USB_Video_Get_Cur_Control_Interface_Requests(controller_ID,
				control_selector,data,size);

		break;

	case GET_INFO:
		status=USB_Video_Get_Info_Control_Interface_Requests(controller_ID,control_selector,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/
/**************************************************************************//*!
 *
 * @name: USB_Video_Set_Control_Interface_Requests 
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
static uint_8 USB_Video_Set_Control_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 bRequest,      
		uint_8 control_selector,
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(bRequest)
	{
	case SET_CUR:
		status=USB_Video_Set_Cur_Control_Interface_Requests(controller_ID,
				control_selector,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;

}/*EndBody*/

static uint_8 USB_Video_Set_Cur_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*EndBody*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Set_Cur_Brightness(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Cur_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Cur_Brightness(controller_ID,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Min_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Min_Brightness(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Max_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Max_Brightness(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Res_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Res_Brightness(controller_ID,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Info_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Info_Brightness(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Def_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case PU_BRIGHTNESS_CONTROL:
		status=USB_Desc_Get_Def_Brightness(controller_ID,data,size);
		break;

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Set_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 bRequest,      
		uint_8 control_selector,
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){

	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*EndBody*/
	switch(bRequest)
	{
	case SET_CUR:
		status=USB_Video_Set_Cur_Processing_Unit(controller_ID,control_selector,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;

}/*EndBody*/

static uint_8 USB_Video_Get_Processing_Unit(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 bRequest,      
		uint_8 control_selector,
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){

	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(bRequest)
	{
	case GET_CUR:
		status=USB_Video_Get_Cur_Processing_Unit(controller_ID,control_selector,data,size);

		break;

	case GET_MIN:
		status=USB_Video_Get_Min_Processing_Unit(controller_ID,control_selector,data,size);
		break;    

	case GET_MAX:
		status=USB_Video_Get_Max_Processing_Unit(controller_ID,control_selector,data,size);
		break; 

	case GET_RES:
		status=USB_Video_Get_Res_Processing_Unit(controller_ID,control_selector,data,size);

		break;

	case GET_LEN:

		break;      

	case GET_INFO:
		status=USB_Video_Get_Info_Processing_Unit(controller_ID,control_selector,data,size);
		break;

	case GET_DEF:
		status=USB_Video_Get_Def_Processing_Unit(controller_ID,control_selector,data,size);
		break;    

	default:
		break;

	}/*EndSwitch*/
	return status;

}/*EndBody*/

/**************************************************************************//*!
 *
 * @name: USB_Video_Get_Control_Interface_Requests 
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
static uint_8 USB_Video_Get_Unit_Terminal_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
  uint_8 i;
  volatile uint_8 j=0;
  uint_8 status = USBERR_INVALID_REQ_TYPE;
  USB_VIDEO_UNITS *entity_desc_data;
  USB_UT_STRUCT_PTR ut_struct;
  uint_8 control_selector;

  control_selector=(uint_8)(setup_packet->value>>8);

  /* get the I/O Interface and Feature  from the descriptor module */
  entity_desc_data = (USB_VIDEO_UNITS *)USB_Desc_Get_Video_Entities(controller_ID);

  for(i=0;i<VIDEO_UNIT_COUNT; i++)
  {
    ut_struct=(USB_UT_STRUCT_PTR)&(entity_desc_data->et[i]);
    if((setup_packet->index >>8) == ut_struct->unit_id)
    {
      switch(ut_struct->type)
      {
        case VC_INPUT_TERMINAL:
          break;

        case VC_PROCESSING_UNIT:
          /* Select SET request Control Processing Unit Module */
           status = USB_Video_Get_Processing_Unit(controller_ID,
           setup_packet->request,control_selector,data,size);
          break;
        case VC_OUTPUT_TERMINAL:

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
 * @name: USB_Video_Set_Control_Interface_Requests 
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
static uint_8 USB_Video_Set_Unit_Terminal_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
  uint_8 i;
  volatile uint_8 j=0;
  uint_8 status = USBERR_INVALID_REQ_TYPE;
  USB_VIDEO_UNITS *entity_desc_data;
  USB_UT_STRUCT_PTR ut_struct;
  uint_8 control_selector;

  control_selector=(uint_8)(setup_packet->value>>8);

  /* get the I/O Interface and Feature  from the descriptor module */
  entity_desc_data = (USB_VIDEO_UNITS *)USB_Desc_Get_Video_Entities(controller_ID);

  for(i=0;i<VIDEO_UNIT_COUNT; i++)
  {
    ut_struct=(USB_UT_STRUCT_PTR)&(entity_desc_data->et[i]);
    if((setup_packet->index >>8) == ut_struct->unit_id)
    {
      switch(ut_struct->type)
      {
        case VC_INPUT_TERMINAL:
          break;

        case VC_PROCESSING_UNIT:
          /* Select SET request Control Feature Unit Module */
           status = USB_Video_Set_Processing_Unit(controller_ID,
           setup_packet->request,control_selector,data,size);
          break;

        case VC_OUTPUT_TERMINAL:
        break;

        default:
        break;
      }
    }
  }
  return status;
}

static uint_8 USB_Video_Set_Cur_Stream_Interface(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case VS_PROBE_CONTROL:
		status=USB_Desc_Set_Cur_Video_Probe(controller_ID,data,size);
		break;

	case VS_COMMIT_CONTROL:
		status=USB_Desc_Set_Cur_Video_Commit(controller_ID,data,size);
		break;

	default:
		break;
	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Cur_Stream_Interface(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case VS_PROBE_CONTROL:
		status=USB_Desc_Get_Cur_Video_Probe(controller_ID,data,size);
		break;

	case VS_COMMIT_CONTROL:
		status=USB_Desc_Get_Cur_Video_Commit(controller_ID,data,size);
		break;

	default:
		break;
	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Len_Stream_Interface(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case VS_PROBE_CONTROL:
		status=USB_Desc_Get_Len_Video_Probe(controller_ID,data,size);
		break;

	case VS_COMMIT_CONTROL:
		status=USB_Desc_Get_Len_Video_Commit(controller_ID,data,size);
		break;

	default:
		break;
	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Get_Info_Stream_Interface(
		uint_8 controller_ID,               /* [IN] Controller ID */
		uint_8 control_selector,            /* [IN] Controller ID */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){
	uint_8 status = USBERR_INVALID_REQ_TYPE;

	/*Body*/
	switch(control_selector){

	case VS_PROBE_CONTROL:
		status=USB_Desc_Get_Info_Video_Probe(controller_ID,data,size);
		break;

	case VS_COMMIT_CONTROL:
		status=USB_Desc_Get_Info_Video_Commit(controller_ID,data,size);
		break;

	default:
		break;
	}/*EndSwitch*/
	return status;
}/*EndBody*/

static uint_8 USB_Video_Set_Stream_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){

	uint_8 status = USBERR_INVALID_REQ_TYPE;
	uint_8 control_selector;

	/*Body*/
	control_selector = (uint_8)(setup_packet->value>>8);
	switch(setup_packet->request)
	{
	case SET_CUR:
		status=USB_Video_Set_Cur_Stream_Interface(controller_ID,control_selector,data,size);

		break;

	default:
		break;

	}/*EndSwitch*/
	return status;

}/*EndBody*/

static uint_8 USB_Video_Get_Stream_Interface_Requests(
		uint_8 controller_ID,               /* [IN] Controller ID */
		USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
		uint_8_ptr *data,                   /* [OUT] Pointer to Data */
		USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
){

	uint_8 status = USBERR_INVALID_REQ_TYPE;
	uint_8 control_selector;

	control_selector = (uint_8)(setup_packet->value>>8);

	/*Body*/
	switch(setup_packet->request)
	{
	case GET_CUR:
		status=USB_Video_Get_Cur_Stream_Interface(controller_ID,control_selector,data,size);

		break;

	case GET_LEN:
		status=USB_Video_Get_Len_Stream_Interface(controller_ID,control_selector,data,size);

		break;      

	case GET_INFO:
		status=USB_Video_Get_Info_Stream_Interface(controller_ID,control_selector,data,size);
		break;  

	default:
		break;

	}/*EndSwitch*/
	return status;
}/*EndBody*/


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
 * Handles Video Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests 
#else
uint_8 USB_Video_Other_Requests 
#endif
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /*[IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
	uint_8 status = USBERR_INVALID_REQ_TYPE;
	uint_8 itf_num,unitID,control_selector;

	/*Body*/
	/* point to the data which comes after the setup packet */
	*data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;

	if (size == NULL)
	{
		return USBERR_GET_MEMORY_FAILED;
	}/*EndIf*/

	itf_num=(uint_8)(setup_packet->index);
	unitID=(uint_8)(setup_packet->index>>8);

	control_selector=(uint_8)(setup_packet->value>>8);

	switch(setup_packet->request_type)
	{
	case GET_REQUEST_ITF:  
		if(itf_num==0)
		{
			/* Video Control Interface is Interface 0 */
			if(0==unitID)
			{
				/* Interface Control Requests */
				status=USB_Video_Get_Control_Interface_Requests(controller_ID,
						setup_packet->request,control_selector,data,size);

			}
			else
			{
				/* Unit and Terminal Requests */
				status=USB_Video_Get_Unit_Terminal_Requests(controller_ID,
						setup_packet,data,size);

			} /*EndIf*/

		}
		else
		{
			/* Video Stream Inteface */
			status=USB_Video_Get_Stream_Interface_Requests(controller_ID,
					setup_packet,data,size);
		} /*EndIf*/

		break; 

	case SET_REQUEST_ITF:
		if(itf_num==0){
			*size = 0;
			/* Video Control Interface is Interface 0 */
			if(0==unitID){
				/* Interface Control Requests */
				status=USB_Video_Set_Control_Interface_Requests(controller_ID,
						setup_packet->request,control_selector,data,size);

			}else{
				/* Unit and Terminal Requests */
				status=USB_Video_Set_Unit_Terminal_Requests(controller_ID,setup_packet,data,size);

			} /*EndIf*/


		}else{
			/* Video Stream Inteface */
			*size=0;

			status=USB_Video_Set_Stream_Interface_Requests(controller_ID,setup_packet,data,size);
		}/*EndIf*/
		break;

	default:
		break;
	} /*EndSwitch*/

	return status;
}/*EndBody*/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_Video_Init
 *
 * @brief   The funtion initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   video_class_callback        : Video Class Callback
 * @param   vendor_req_callback         : Vendor Request Callback
 * @param   param_callback              : Class requests Callback
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the Video Class layer and layers it is dependent on
 *****************************************************************************/
uint_8 USB_Class_Video_Init (
		uint_8    controller_ID,                  /* [IN] Controller ID */
		USB_CLASS_CALLBACK video_class_callback,  /* [IN] Video Class Callback */
		USB_REQ_FUNC       vendor_req_callback,   /* [IN] Vendor Request Callback */
		USB_CLASS_CALLBACK param_callback         /* [ IN] Video Class requests Callback */
)
{
    uint_8 index;
    uint_8 status = USB_OK;
    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(controller_ID);

#ifndef COMPOSITE_DEV
    /* Initialize the device layer*/
    status = _usb_device_init(controller_ID,NULL,
        (uint_8)(ep_desc_data->count+1), TRUE);
    if(status == USB_OK)
    {
        /* Initialize the generic class functions */
        status = USB_Class_Init(controller_ID,USB_Class_Video_Event,
            USB_Other_Requests);

        if(status == USB_OK)
        {
#endif
            g_video_endpoint_data.count = ep_desc_data->count;

            for(index = 0; index < ep_desc_data->count; index++)
            {
                g_video_endpoint_data.ep[index].endpoint =
                    ep_desc_data->ep[index].ep_num;
                g_video_endpoint_data.ep[index].type =
                    ep_desc_data->ep[index].type;
                g_video_endpoint_data.ep[index].bin_consumer = 0x00;
                g_video_endpoint_data.ep[index].bin_producer = 0x00;
                g_video_endpoint_data.ep[index].queue_num    = 0x00;
            }

            /* save the video class callback pointer */
            g_video_class_callback = video_class_callback;

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
 * @name  USB_Class_Video_DeInit
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
 *This function de-initializes the Video Class layer
 *****************************************************************************/
uint_8 USB_Class_Video_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status = USB_OK;
#ifdef COMPOSITE_DEV
    UNUSED(controller_ID)
#endif
    /* free the Audio class callback pointer */
    g_video_class_callback = NULL;
        
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
 * @name  USB_Class_Video_Send_Data
 *
 * @brief This fucntion is used by Application to send data through Video class
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
 * This fucntion is used by Application to send data through Video class
 *****************************************************************************/
uint_8 USB_Class_Video_Send_Data (
		uint_8 controller_ID,       /* [IN] Controller ID */
		uint_8 ep_num,              /* [IN] Endpoint Number */
		uint_8_ptr app_buff,        /* [IN] Buffer to Send */
		USB_PACKET_SIZE size        /* [IN] Length of the Transfer */
)
{
	uint_8 status = USB_OK;
	PTR_USB_CLASS_VIDEO_QUEUE queue_tmp;

#if IMPLEMENT_QUEUING
	uint_8 index;
	uint_8 producer, queue_num;

	USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
                                    		USB_Desc_Get_Endpoints(controller_ID);

	/*Body*/                                    
	/* map the endpoint num to the index of the endpoint structure */

	for(index = 0; index < usb_ep_data->count; index++) 
	{
		if(usb_ep_data->ep[index].ep_num == ep_num)
			break;
	}/*EndFor*/

	producer = g_video_endpoint_data.ep[index].bin_producer;
	queue_num = g_video_endpoint_data.ep[index].queue_num;

	if(MAX_QUEUE_ELEMS != queue_num)
	{
		/* the bin is not full*/
		/* put all send request parameters in the endpoint data structure */
		queue_tmp = &(g_video_endpoint_data.ep[index].queue[producer]);
		queue_tmp->controller_ID  = controller_ID;
		queue_tmp->channel        = ep_num;
		queue_tmp->app_buff       = app_buff;
		queue_tmp->size           = size;

		/* increment producer bin by 1*/
		if (producer == (MAX_QUEUE_ELEMS - 1))
		{
			g_video_endpoint_data.ep[index].bin_producer = 0;
		} /*Else*/
		else 
		{
			g_video_endpoint_data.ep[index].bin_producer++;
		}/*EndElse*/
		g_video_endpoint_data.ep[index].queue_num++;

		if(g_video_endpoint_data.ep[index].queue_num == 1)
		{
#endif
			status = USB_Class_Send_Data(controller_ID, ep_num, app_buff,size);
#if IMPLEMENT_QUEUING
		}/*EndIf*/
	}/*Else*/
	else /* bin is full */
	{
		status = USBERR_DEVICE_BUSY;
	}/*EndIf*/
#endif
	return status;
}/*EndBody*/
