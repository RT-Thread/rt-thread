/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @file usb_msc.c
 *
 * @author 
 *
 * @version 
 *
 * @date May-08-2009
 *
 * @brief The file contains USB stack MSC layer implimentation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_msc.h"
#include "usb_descriptor.h"
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
 /* Add all the variables needed for usb_msc.c to this structure */
 MSC_GLOBAL_VARIABLE_STRUCT g_msc;
 
static uint_32 g_current_offset = 0;
static uint_32 g_transfer_remaining = 0;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests
#else
uint_8 USB_MSC_Other_Requests
#endif
		(uint_8 controller_ID,
		USB_SETUP_STRUCT * setup_packet, 
		uint_8_ptr *data, 
		uint_32 *size);
uint_8 process_mass_storage_command (uint_8 controller_ID,
		PTR_CBW cbw_ptr, 
		uint_32* csw_residue_ptr, 
		uint_8* csw_status_ptr);                           
                          
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
 
 /*****************************************************************************
 * Local Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  process_mass_storage_command
 *
 * @brief Process a Mass storage class command 
 *        This function is added here to add more sub class specific commands)
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 process_mass_storage_command 
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr, 
    uint_32* csw_residue_ptr, 
    uint_8* csw_status_ptr
)
{   
    uint_8 error = USBERR_UNKNOWN_ERROR;/* initializing to error value */
    switch (cbw_ptr->command_block[0]) 
    {
        /* commands to be supported by all devices */
        case INQUIRY_COMMAND : /*opcode : 0x12*/
            error = msc_inquiry_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;
        case READ_10_COMMAND : /*opcode : 0x28 */
        case READ_12_COMMAND : /*opcode : 0xA8 */
            error = msc_read_command(controller_ID, cbw_ptr,csw_residue_ptr,csw_status_ptr);
            break;    	
        case REQUEST_SENSE_COMMAND : /*opcode : 0x03*/
            error = msc_request_sense_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
           break;           
        case TEST_UNIT_READY_COMMAND : /*opcode : 0x00 */ 
            error = msc_test_unit_ready_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break; 
        case WRITE_10_COMMAND : /*opcode : 0x2A */
        case WRITE_12_COMMAND : /*opcode : 0xAA */
            error = msc_write_command(controller_ID, cbw_ptr,csw_residue_ptr,csw_status_ptr);
            break; 
        case PREVENT_ALLOW_MEDIUM_REM_COMMAND : /*opcode :0x1E */
            error = msc_prevent_allow_medium_removal(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;                   
        case FORMAT_UNIT_COMMAND : /*opcode : 0x04*/
            error = msc_format_unit_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;
        case READ_CAPACITY_10_COMMAND : /*opcode : 0x25*/
            error = msc_read_capacity_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;       
        case MODE_SENSE_10_COMMAND : /* opcode :0x5A*/
        case MODE_SENSE_6_COMMAND : /* opcode : 0x1A */
            error = msc_mode_sense_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;
        case MODE_SELECT_10_COMMAND : /*opcode : 0x55 */
        case MODE_SELECT_6_COMMAND : /*opcode : 0x15 */
            error = msc_mode_select_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            break;
    	case READ_FORMAT_CAPACITIES_COMMAND : /*opcode : 0x23 */
    		error = msc_read_format_capacity_command(controller_ID, cbw_ptr,csw_residue_ptr,
    			csw_status_ptr);
    		break;
    	case SEND_DIAGNOSTIC_COMMAND : /*opcode : 0x1D*/
    		error = msc_send_diagnostic_command(controller_ID, cbw_ptr,csw_residue_ptr,
    			csw_status_ptr);
			break; 
    	case VERIFY_COMMAND : /*opcode : 0x2F*/
    		error = msc_verify_command(controller_ID, cbw_ptr,csw_residue_ptr,csw_status_ptr);
			break;
    	case START_STOP_UNIT_COMMAND : /*opcode : 0x1B*/
    		error = msc_start_stop_unit_command(controller_ID, cbw_ptr,csw_residue_ptr,csw_status_ptr);
  			break;     	     	
        default: /* for all unsupported commands */
            error = msc_unsupported_command(controller_ID, cbw_ptr,csw_residue_ptr,
            	csw_status_ptr);
            g_msc.out_flag = FALSE;
            g_msc.in_flag = FALSE;
            g_msc.out_stall_flag = FALSE;
            g_msc.in_stall_flag = FALSE;
            break;
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Bulk_In
 *
 * @brief The funtion ic callback function of DIC Bulk In Endpoint 
 *
 * @param event
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Service_Bulk_In(PTR_USB_DEV_EVENT_STRUCT event)
{
    uint_8 event_type; 
    
	#if IMPLEMENT_QUEUING    
	    uint_8 index;
	    uint_8 producer, consumer;
	    USB_ENDPOINTS *usb_ep_data = USB_Desc_Get_Endpoints(event->controller_ID); 
	    
	    USB_CLASS_MSC_QUEUE queue;
	    /* map the endpoint num to the index of the endpoint structure */
	    for(index = 0; index < usb_ep_data->count; index++) 
	    {
	        if(usb_ep_data->ep[index].ep_num == event->ep_num)
	        break;
	    }
	                                               
	    producer = g_msc.ep[index].bin_producer;	        
	    /* if there are no errors de-queue the queue and decrement the no. of 
	       transfers left, else send the same data again */
	    g_msc.ep[index].bin_consumer++;  	        
	    consumer = g_msc.ep[index].bin_consumer;	        
	    
	    if(consumer != producer) 
	    {/*if bin is not empty */
	                        
	        queue = g_msc.ep[index].queue[consumer%MAX_QUEUE_ELEMS];	                        
	        (void)USB_Class_Send_Data(queue.controller_ID, queue.channel, 
	        	queue.app_data.data_ptr, queue.app_data.data_size);
			return;                           
	    }          
	#endif
     
    if(g_transfer_remaining >= event->len)
    {	/* decrement the global count */
		g_transfer_remaining -= event->len;        	
	 }
        
    /* check if there is need to stall BULK IN ENDPOINT And
       there isn't any transfer in progress*/
    if((g_msc.in_stall_flag == TRUE)&&(!g_transfer_remaining))
    {
       	uint_8 component = (uint_8)(event->ep_num | 
            (uint_8)(event->direction<<COMPONENT_PREPARE_SHIFT));
       	g_msc.in_stall_flag = FALSE; /* clear the flag */
       	g_msc.in_flag = FALSE; /* clear send flag */
       	/* now, stalling the status phase - CASE 5th of THIRTEEN CASES*/           
		(void)_usb_device_set_status(&(event->controller_ID),
			(uint_8)(component|USB_STATUS_ENDPOINT),(uint_16)USB_STATUS_STALLED);
		return;					
    }

    /* If its not a data phase on bulk endpoint */
    if ((!g_msc.in_flag) && (event->len == MSC_CSW_LENGTH)) 
    {
      	USB_memcopy(event->buffer_ptr, &(g_msc.csw_struct), sizeof(CSW));
    } 
   
    if(g_msc.in_flag) /* bulk in transaction has occurred before CSW */
    {                           
        if(g_msc.param_callback != NULL) 
        {
 			    event_type = (uint_8)(g_transfer_remaining?
 				    USB_MSC_DEVICE_READ_REQUEST : USB_APP_SEND_COMPLETE);
       		
 			    if(event_type == USB_APP_SEND_COMPLETE)
 			    {       
            		APP_DATA_STRUCT bulk_in_recv;
            		bulk_in_recv.data_ptr = event->buffer_ptr;
            		bulk_in_recv.data_size = event->len; 
                	g_msc.param_callback(event->controller_ID, event_type,
                		(void*)&bulk_in_recv);
            	}
            	else
            	{
				      LBA_APP_STRUCT lba_data;		
				      g_current_offset += event->len;
				      lba_data.offset = g_current_offset;
			      	lba_data.size = (g_transfer_remaining > MSC_SEND_DATA_BUFF_SIZE) ? 
				          	MSC_SEND_DATA_BUFF_SIZE : g_transfer_remaining; 
				     /* whichever is smaller */
				     lba_data.buff_ptr = g_msc.msc_lba_send_buff;

	  			   g_msc.param_callback(event->controller_ID, USB_MSC_DEVICE_READ_REQUEST,
	  				          (void*)&lba_data);
    			   (void)USB_MSC_Bulk_Send_Data(event->controller_ID, lba_data.buff_ptr, 
    				         lba_data.size);	
        	    }
        }        
        
        if(!g_transfer_remaining)
        {	/* marks the end of data phase */
	        g_msc.in_flag = FALSE; /* clear the flag for next CBW */	        
	        /* Send the command status information */
    	    (void)USB_MSC_Bulk_Send_Data(event->controller_ID, 
    	    	(uint_8_ptr)&(g_msc.csw_struct), MSC_CSW_LENGTH);                	
        }
    } 
    else if ((event->len == MSC_CSW_LENGTH) /* CSW is 13 bytes in length */
    	&& (g_msc.csw_struct.signature == USB_DCSWSIGNATURE)) /*valid CSW signature*/       	      
    {
        /* this flag will now be set on reset or after CSW being sent */
        g_msc.cbw_valid_flag = TRUE;        
        /* prepare for next CBW */  
        (void)USB_MSC_Bulk_Recv_Data(&(event->controller_ID),
            (uint_8_ptr)&(g_msc.cbw_struct),MSC_CBW_LENGTH);
    }     
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Bulk_Out
 *
 * @brief The function is callback function of DIC Bulk Out Endpoint 
 *
 * @param event
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Service_Bulk_Out(PTR_USB_DEV_EVENT_STRUCT event)
{       
    uint_8 event_type; 
    uint_8 error;
    
    /* check if there is need to stall BULK OUT ENDPOINT And 
       there isn't any transfer in progress*/
    if((g_msc.out_stall_flag == TRUE)&&(!g_transfer_remaining))
    {
       	uint_8 component = (uint_8)(event->ep_num | 
        	(event->direction<<COMPONENT_PREPARE_SHIFT));
       	g_msc.out_stall_flag = FALSE; /* clear the flag */
       	g_msc.out_flag = FALSE; /* clear send flag */
       	/* now, stalling the status phase - CASE 5th of THIRTEEN CASES*/           
		(void)_usb_device_set_status(&(event->controller_ID),
		    (uint_8)(component|USB_STATUS_ENDPOINT),
			(uint_16)USB_STATUS_STALLED);
		return;					
    }
    
    /* If its not a data phase on bulk endpoint */
    if ((!g_msc.out_flag) && (event->len == MSC_CBW_LENGTH) && 
        (event->buffer_ptr != (uint_8_ptr)&(g_msc.cbw_struct)) )
    {   /* last check condition saves memcopy overhead in case data was 
           already received in correct buffer */
      	USB_memcopy(event->buffer_ptr, (uint_8_ptr)&(g_msc.cbw_struct), 
      	    sizeof(CBW));
    }     
    
    if(g_msc.out_flag) /* bulk out transaction has occurred after CBW */
    {        
        if(g_msc.param_callback != NULL) 
        {
 		    	event_type = (uint_8)(g_transfer_remaining?
 				    USB_MSC_DEVICE_WRITE_REQUEST : USB_APP_DATA_RECEIVED);
 			
			    if(event_type == USB_APP_DATA_RECEIVED)
 		    	{
    				APP_DATA_STRUCT bulk_out_recv;				    
    		        bulk_out_recv.data_ptr = event->buffer_ptr;
    		        bulk_out_recv.data_size = event->len; 
     				g_msc.param_callback(event->controller_ID, event_type,(void*)&bulk_out_recv);	
 			    }
 			    else
 			    {
     				LBA_APP_STRUCT lba_data1;
     				lba_data1.buff_ptr = g_msc.msc_lba_recv_buff;
     				lba_data1.offset = g_current_offset;
     				lba_data1.size = event->len; 				    			
     				g_msc.param_callback(event->controller_ID, event_type,(void*)&lba_data1);            
     			}            
        }
        
        if(g_transfer_remaining >= event->len)
        {	/* decrement the global count */
			      g_transfer_remaining -= event->len;
			      			      
			if((g_msc.out_stall_flag == TRUE)&&(!g_transfer_remaining))
            {
       	        uint_8 component = (uint_8)(event->ep_num | 
        	        (event->direction<<COMPONENT_PREPARE_SHIFT));
               	g_msc.out_stall_flag = FALSE; /* clear the flag */
               	g_msc.out_flag = FALSE; /* clear send flag */
               	/* now, stalling the status phase - CASE 5th of THIRTEEN CASES*/           
        		(void)_usb_device_set_status(&(event->controller_ID),
        			    (uint_8)(component|USB_STATUS_ENDPOINT),
        			    (uint_16)USB_STATUS_STALLED);
        		return;					
            }
        }
        
        if(g_transfer_remaining)
        {	/* Transfers Remaining -- Again invoke recv_data */   			
	        LBA_APP_STRUCT lba_data0;	        
	        g_current_offset += event->len;
	        lba_data0.size = (g_transfer_remaining > MSC_RECV_DATA_BUFF_SIZE) ? 
	            MSC_RECV_DATA_BUFF_SIZE : g_transfer_remaining; /* whichever is smaller */
	        lba_data0.buff_ptr = g_msc.msc_lba_recv_buff;    	    	
    	    (void)USB_MSC_Bulk_Recv_Data(&(event->controller_ID),
    	    	lba_data0.buff_ptr,lba_data0.size);
        	return;
        	
        }
        else
        {	/* marks the end of data phase */
   	        g_msc.out_flag = FALSE; /* clear the flag for next CBW */
        	/* Send the command status information */
        	(void)USB_MSC_Bulk_Send_Data(event->controller_ID, 
        		(uint_8_ptr)&(g_msc.csw_struct), MSC_CSW_LENGTH);         	
        }
    } 
    else if(/* check for valid and meaningful CBW */
        /* CBW received after device had sent a CSW or after a reset */
        (g_msc.cbw_valid_flag)         
        /* CBW is 31 bytes in length */
        && (event->len == MSC_CBW_LENGTH) 
        /* valid CBW signature*/
        && (g_msc.cbw_struct.signature == USB_DCBWSIGNATURE) 
        /* all reserved bits should be zero*/
        && (!((g_msc.cbw_struct.lun & 0xF0) || (g_msc.cbw_struct.cb_length & 0xE0)))         
        /* host should send command to valid LUN */
        && (g_msc.cbw_struct.lun<g_msc.device_info.num_lun_supported)        							
        /* valid cbwcb length*/
        && ((g_msc.cbw_struct.cb_length >= 0x01)&&(g_msc.cbw_struct.cb_length <= 0x10))        												
          )
    {
        g_msc.re_stall_flag = TRUE;
        /* A valid CBW was received */
        g_msc.csw_struct.signature = USB_DCSWSIGNATURE;
        g_msc.csw_struct.tag = g_msc.cbw_struct.tag;
        /*this flag will now be set on reset or after CSW being sent */
        g_msc.cbw_valid_flag = FALSE;
		
	    USB_BYTE_SWAP4((uint_32)g_msc.cbw_struct.data_length,(uint_32*)&(g_msc.cbw_struct.data_length));
		
        /* set flag if device is going to recv data in coming transaction */
        g_msc.out_flag = (boolean)(( (!(g_msc.cbw_struct.flag & USB_CBW_DIRECTION_BIT))
        	&& (g_msc.cbw_struct.data_length))?TRUE:FALSE);
        /* set flag if send is going to send data in coming transaction */
        g_msc.in_flag = (boolean)(( (g_msc.cbw_struct.flag & USB_CBW_DIRECTION_BIT)
            && (g_msc.cbw_struct.data_length))?TRUE:FALSE);                
        /* Process the command */
        error = process_mass_storage_command(event->controller_ID, &(g_msc.cbw_struct), 
        	(uint_32*)&(g_msc.csw_struct.residue), &(g_msc.csw_struct.csw_status));
		
		if(error == USBERR_ENDPOINT_STALLED)
		{
			if(g_msc.out_flag==TRUE)
			{
				g_msc.out_stall_flag = TRUE;	
				g_msc.out_flag = FALSE; /* so as to send status phase */
			}
			else if(g_msc.in_flag==TRUE)
			{
				g_msc.in_stall_flag = TRUE;	
			}			
		}
        
        /* if there is no data phase on bulk endpoints */
        if(!(g_msc.out_flag || g_msc.in_flag)) 
        {   /* Send the command status information */
            (void)USB_MSC_Bulk_Send_Data(event->controller_ID, 
              (uint_8_ptr)&(g_msc.csw_struct), MSC_CSW_LENGTH);         
        }
    } 
    else /* Invalid/NMreceived */
    {        
        uint_8 direction;
        uint_8 ep_num;
        /* prepare the component to be sent in lower layer with 
           endpoint number and direction*/
        uint_8 component;
        
        direction  = USB_RECV; 
        ep_num = BULK_OUT_ENDPOINT;
        component = (uint_8)(ep_num | (direction<<COMPONENT_PREPARE_SHIFT));

        /* in case of error Stall endpoint and update the status */        
		    (void)_usb_device_set_status(&(event->controller_ID),
			    (uint_8)(component | USB_STATUS_ENDPOINT),
			    (uint_16)USB_STATUS_STALLED);

        direction  = USB_SEND;
        ep_num = BULK_IN_ENDPOINT;
        component = (uint_8)(ep_num | (direction << COMPONENT_PREPARE_SHIFT));

        /* in case of error Stall endpoint and update the status*/        
		    (void)_usb_device_set_status(&(event->controller_ID),
					(uint_8)(component | USB_STATUS_ENDPOINT),
					(uint_16)USB_STATUS_STALLED);
		    /* make the following CBWs invalid */
		    g_msc.cbw_valid_flag = FALSE;
    }    
}


/**************************************************************************//*!
 *
 * @name  USB_Class_MSC_Event
 *
 * @brief The funtion initializes MSC endpoints 
 *
 * @param controller_ID:        To identify the controller   
 * @param event           pointer to event structure
 * @param val             gives the configuration value 
 *
 * @return None       
 *
 *****************************************************************************/
 void USB_Class_MSC_Event(uint_8 controller_ID, uint_8 event, void* val) 
{	
#if IMPLEMENT_QUEUING    
    uint_8 index;
#endif    
    /* get the endpoints from the descriptor module */            
    USB_ENDPOINTS *usb_ep_data = USB_Desc_Get_Endpoints(controller_ID); 
        
    if(event == USB_APP_ENUM_COMPLETE)
    {
        uint_8 index_num = 0;
        uint_8 count = 0,ep_count = 0;  
        
#ifdef COMPOSITE_DEV
        DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
        CLASS_ARC_STRUCT_PTR dev_class_ptr;   
        dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);    
        for(count = 0; count < dev_arc_ptr->cl_count; count++)
        {
            dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
            /* Initializes sub_classes */
            ep_count = dev_class_ptr->value[0];
            if(dev_class_ptr->class_type == 0x08/*MSD_CC*/)
                break;
            index_num +=dev_class_ptr->value[0];
        }
#else                    		    
		ep_count = usb_ep_data->count; 
#endif
		/* deinitialize all endpoints in case they were initialized */
		for(count=index_num; count<ep_count+index_num; count++) 
 		    {   
    		USB_EP_STRUCT_PTR ep_struct_ptr= 
    				(USB_EP_STRUCT_PTR) (&usb_ep_data->ep[count]);
    		(void)_usb_device_deinit_endpoint(&controller_ID,
    				ep_struct_ptr->ep_num, ep_struct_ptr->direction);
    	}

        /* intialize all non control endpoints */            
        for(count=index_num; count<ep_count+index_num; count++) 
        {
    		USB_EP_STRUCT_PTR ep_struct_ptr= 
    				(USB_EP_STRUCT_PTR) (&usb_ep_data->ep[count]);
    		uint_8 component = (uint_8)(ep_struct_ptr->ep_num | 
    				(ep_struct_ptr->direction<<COMPONENT_PREPARE_SHIFT));       	

    		(void)_usb_device_init_endpoint(&controller_ID,ep_struct_ptr->ep_num,
    				(uint_16)ep_struct_ptr->size, ep_struct_ptr->direction, ep_struct_ptr->type, FALSE);

#ifdef MULTIPLE_DEVICES
    		/* register callback service for Non Control EndPoints */
    		if(ep_struct_ptr->type == USB_BULK_PIPE) 
    		{             
    			if(ep_struct_ptr->direction == USB_RECV) 
    			{
    				(void)_usb_device_register_service(controller_ID,
    						(uint_8)(USB_SERVICE_EP0+ep_struct_ptr->ep_num),
    						USB_Service_Bulk_Out);
    			}
    			else
    			{
    				(void)_usb_device_register_service(controller_ID,
    						(uint_8)(USB_SERVICE_EP0+ep_struct_ptr->ep_num),
    						USB_Service_Bulk_In);
    			}            
    		}
#endif

    		/* set the EndPoint Status as Idle in the device layer */
    		/* (no need to specify direction for this case) */
    		(void)_usb_device_set_status(&controller_ID,
    				(uint_8)(USB_STATUS_ENDPOINT|component),
    				(uint_16)USB_STATUS_IDLE);                                                                                                         
    	}
    	g_msc.re_stall_flag = FALSE;
    	g_msc.out_flag = FALSE;
    	g_msc.in_flag = FALSE;
    	g_msc.out_stall_flag = FALSE;
    	g_msc.in_stall_flag = FALSE;
    	g_msc.cbw_valid_flag = TRUE; /*making the first CBW valid */ 
    	g_transfer_remaining = 0; 
    }
    else if(event == USB_APP_BUS_RESET)
    {
#if IMPLEMENT_QUEUING
    	for(index = 0; index < usb_ep_data->count; index++) 
    	{
    		g_msc.ep[index].bin_consumer = 0x00;         
    		g_msc.ep[index].bin_producer = 0x00;        
    	}
#endif 
    }
    else if(event == USB_APP_EP_UNSTALLED)
    {
    	uint_8 value;
    	value = *((uint_8_ptr)val);

    	if( (g_msc.re_stall_flag == TRUE)
    			&&
    			(((value & 0x0F) == BULK_IN_ENDPOINT) || 
    					((value & 0x0F) == BULK_OUT_ENDPOINT)))
    	{	/* For MASS Storage Class BULK ENDPOINTS have to be unstalled 
    		       only on receiving Bulk Only Reset. 
    		       Therefore, if Host sends clear feature to unstall these 
    		       endpoints, re-stall them */    		              
    		(void)_usb_device_set_status(&controller_ID,
    				(uint_8)(value|USB_STATUS_ENDPOINT),
    				(uint_16)USB_STATUS_STALLED);
    	}    	
    }
    else if(event == USB_APP_EP_STALLED)
    {
    	/* Code to be added here, 
		       if there is some action needed at app level */	    	
    }

    if(g_msc.msc_callback != NULL) 
    {
    	g_msc.msc_callback(controller_ID,event,val);
    } 
}

/**************************************************************************//*!
 *
 * @name  USB_Other_Requests
 *
 * @brief The funtion provides flexibilty to add class and vendor specific
 *        requests 
 *
 * @param controller_ID:        To identify the controller
 * @param setup_packet:     setup packet received      
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return status:       
 *                        USB_OK : When Successfull       
 *                        Others : When Error
 *
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests
#else
uint_8 USB_MSC_Other_Requests
#endif
(
	uint_8 controller_ID,
	USB_SETUP_STRUCT * setup_packet, 
  uint_8_ptr *data, 
  uint_32 *size
) 
{
     uint_8 error = USBERR_INVALID_REQ_TYPE;  
     
     *size=0;
     
     if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) == 
     	USB_REQUEST_CLASS_CLASS) 
     {  /* class request so handle it here */
     
        error = USB_OK;
		
        /* call for class/subclass specific requests */
        switch(setup_packet->request) 
        {
            case GET_MAX_LUN :
         		if((setup_packet->index < USB_MAX_SUPPORTED_INTERFACES)&&
          	    	(!setup_packet->value)&&(setup_packet->length == 0x0001)&&
          	        ((setup_packet->request_type & USB_DATA_DIREC_MASK) == 
          	       	USB_DATA_TO_HOST))
        	    {
        	  		/* return the maximum number of logical units supported */
                    *data = &g_msc.lun;
            		*size=1;
            		g_msc.re_stall_flag = TRUE;
        	    }
        	    else 
        	    {   /* for Get Max LUN request with invalid wIndex parameter, 
        	    	   host expects stall */
        	    	error = USBERR_INVALID_REQ_TYPE; 
         	    }              
              break;
            case BULK_ONLY_MASS_STORAGE_RESET :
                /* Steps to be taken in this command :
                1) ready the device for the next CBW from the host
                2) preserve the value of its bulk data toggle bits 
                3) preserve the value of its bulk endpoint STALL conditions
                4) device shall NAK the status stage of device request until 
                   command is complete*/
                if((setup_packet->index < USB_MAX_SUPPORTED_INTERFACES)&&
          	        (!setup_packet->value)&&(!setup_packet->length) &&
          	        ((setup_packet->request_type & USB_DATA_DIREC_MASK) == 
          	       	USB_DATA_TO_DEVICE))
          	    {
                    /* get the endpoints from the descriptor module */            
                    USB_ENDPOINTS *usb_ep_data = USB_Desc_Get_Endpoints(controller_ID);
                    uint_8 count;
                    count = 0; 
                    /* deinitialize and initialize bulk endpoints */            
                    while(count < usb_ep_data->count) 
                    {
                        USB_EP_STRUCT_PTR ep_struct_ptr= 
                        (USB_EP_STRUCT_PTR) (&usb_ep_data->ep[count]);
                        if(ep_struct_ptr->type == USB_BULK_PIPE)
                        {
                            uint_8 component = (uint_8)(ep_struct_ptr->ep_num | 
                                (ep_struct_ptr->direction<<COMPONENT_PREPARE_SHIFT));
                            (void)_usb_device_set_status(&controller_ID,(uint_8)
                            (USB_STATUS_ENDPOINT|component),
                            (uint_16)USB_STATUS_STALLED);
                            /* set EndPoint Status as Idle */        				
                            (void)_usb_device_set_status(&controller_ID,(uint_8)
                            (USB_STATUS_ENDPOINT|component),
                            (uint_16)USB_STATUS_IDLE);
                        }
                        count++;
                    }
                    g_msc.out_flag = FALSE;
                    g_msc.in_flag = FALSE;
                    g_msc.out_stall_flag = FALSE;
                    g_msc.in_stall_flag = FALSE;
  					g_msc.cbw_valid_flag = TRUE; /*making the first CBW valid */               
  					g_msc.re_stall_flag = FALSE;
  					g_transfer_remaining = 0; 
          	    }
          	    else 
          	    {   /* for Get Max LUN request with invalid wIndex parameter, 
          	    	   host expects stall */
          	    	error = USBERR_INVALID_REQ_TYPE; 
           	    }    
                break;           
          	default :break;        
        }
    } 
    else if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) == 
     	USB_REQUEST_CLASS_VENDOR) 
    {   /* vendor specific request  */    
        if(g_msc.vendor_callback != NULL) 
        {
            error = g_msc.vendor_callback(controller_ID, setup_packet,data,size);
        }
    }
     
    return error;
}


/*****************************************************************************
 * Global Functions
 *****************************************************************************/
#if(defined LITTLE_ENDIAN)
	/* SWAP four consecutive bytes to correct the endianness of data received*/
	void USB_BYTE_SWAP4(uint_32 a, uint_32* b) 
	{
		*b = a;
	}

 
#else
	/* SWAP four consecutive bytes to correct the endianness of data received*/
	void USB_BYTE_SWAP4(uint_32 a, uint_32* b) 
	{
	   uint_32 c = (a & 0x000000ff) << (uint_32)24;
	   c |= (a & 0x0000ff00) << (uint_32)8;
	   c |= (a & 0x00ff0000) >> (uint_32)8;
	   c |= (a & 0xff000000) >> (uint_32)24;
	   *b=c;
	}
#endif
	
 /* To clear the buffer */
 void USB_memzero(void* ptr, uint_32 size) 
 {
    uint_32 index;
    for(index = 0; index < size; index++) 
    {
        *((uint_8_ptr)ptr + index) = 0x00;        
    }
 }

 /* To copy data from one memory location to another */ 
 void USB_memcopy(void* src, void* dst, uint_32 size) 
 {
    uint_32 index;
    
    for(index = 0; index < size; index++) 
    {
        *((uint_8_ptr)dst + index) = *((uint_8_ptr)src + index);        
    }
 }
  
/**************************************************************************//*!
 *
 * @name  USB_Class_MSC_Init
 *
 * @brief The funtion initializes the Device and Controller layer 
 *
 * @param controller_ID:        To Identify the controller
 * @param class_callback:   event callback      
 * @param vendor_req_callback:  vendor specific class request callback      
 * @param param_callback:       application params callback      
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 ******************************************************************************
 *
 *This function initializes the MSC Class layer and layers it is dependednt on 
 ******************************************************************************/
uint_8 USB_Class_MSC_Init
(
    uint_8 controller_ID,/*[IN] the USB device controller to initialize*/
    USB_CLASS_CALLBACK msc_class_callback,
    USB_REQ_FUNC       vendor_req_callback,                               
    USB_CLASS_CALLBACK param_callback
)
{
	#if IMPLEMENT_QUEUING    
	    uint_8 index;
	#endif    
	uint_8 error;   
	USB_ENDPOINTS *usb_ep_data = USB_Desc_Get_Endpoints(controller_ID); 
    
    /* initialize the Global Variable Structure */
	USB_memzero(&g_msc, sizeof(MSC_GLOBAL_VARIABLE_STRUCT));

#ifndef COMPOSITE_DEV		
    /* Initialize the device layer*/
    error= _usb_device_init(controller_ID, NULL, (uint_8)(usb_ep_data->count+1), TRUE);
    /* +1 is for Control Endpoint */
    
    
	 /* Initialize number of Logical Units */
    if(error == USB_OK) 
    {
        /* Initialize the generic class functions */
        error = USB_Class_Init(controller_ID,USB_Class_MSC_Event,
        	USB_Other_Requests);
#endif
        /* Initialize the pstn subclass functions */
        error = USB_MSC_SCSI_Init(controller_ID, param_callback);

		#if IMPLEMENT_QUEUING
	        for(index = 0; index < usb_ep_data->count; index++) 
	        {
	            g_msc.ep[index].endpoint = usb_ep_data->ep[index].ep_num;
	            g_msc.ep[index].type = usb_ep_data->ep[index].type;        
	            g_msc.ep[index].bin_consumer = 0x00;         
	            g_msc.ep[index].bin_producer = 0x00;        
	        }
		#endif
        
        if(error == USB_OK) 
        {
           /* save the callback pointer */
           g_msc.msc_callback = msc_class_callback;
           
           /* save the callback pointer */
           g_msc.vendor_callback = vendor_req_callback;
           
           /* save the callback pointer */
           g_msc.param_callback = param_callback;           
        }          
#ifndef COMPOSITE_DEV       
    }  
#endif

    if(g_msc.param_callback != NULL) 
    {				
		    g_msc.param_callback(controller_ID, USB_MSC_DEVICE_GET_INFO, &g_msc.device_info);	
    }
  	
  	/* Initialize number of Logical Units */
	  g_msc.lun = (uint_8)(g_msc.device_info.num_lun_supported-1);
    
    return error;     
}

/**************************************************************************//*!
 *
 * @name  USB_Class_MSC_DeInit
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
 *This function de-initializes the MSC Class layer
 *****************************************************************************/
uint_8 USB_Class_MSC_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status = USB_OK;
#ifdef COMPOSITE_DEV
    UNUSED(controller_ID)
#endif
    
    /* free the HID class callback pointer */
    g_msc.msc_callback = NULL;
    
    /* free the vendor request callback pointer */
    g_msc.vendor_callback = NULL;
    
    /* free the callback to ask application for class specific params*/
    g_msc.param_callback = NULL;
    
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
 * @name  USB_Class_MSC_Send_Data
 *
 * @brief 
 *
 * @param controller_ID:        To identify the controller   :   
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/
uint_8 USB_Class_MSC_Send_Data
(
	uint_8 controller_ID,
	uint_8 ep_num,
	uint_8_ptr app_buff,
	uint_32 size
) 
{
    uint_8 error = USB_OK;

	#if IMPLEMENT_QUEUING    
	    uint_8 index;
	    uint_8 producer, consumer;       
	    
	    USB_ENDPOINTS *usb_ep_data = USB_Desc_Get_Endpoints(controller_ID); 
	  
	    /* map the endpoint num to the index of the endpoint structure */
	    for(index = 0; index < usb_ep_data->count; index++) 
	    {
	        if(usb_ep_data->ep[index].ep_num == ep_num)
	        break;
	    }
	    
	    producer = g_msc.ep[index].bin_producer;
	    consumer = g_msc.ep[index].bin_consumer;
	                            
	    if(((uint_8)(producer - consumer)) != (uint_8)(MAX_QUEUE_ELEMS))  
	    {/* the bin is not full*/	    
	        uint_8 queue_num = (uint_8)(producer % MAX_QUEUE_ELEMS);
	        
	        /* put all send request parameters in the endpoint data structure*/
	        g_msc.ep[index].queue[queue_num].channel = ep_num;
	        g_msc.ep[index].queue[queue_num].app_data.data_ptr = app_buff;
	        g_msc.ep[index].queue[queue_num].app_data.data_size = size;
	        g_msc.ep[index].queue[queue_num].controller_ID = controller_ID; 
	        
	        /* increment producer bin by 1*/       
	        g_msc.ep[index].bin_producer = ++producer;
	                
	        if((uint_8)(producer - consumer) == (uint_8)1)         
	        {          
	#endif            
         		error = USB_Class_Send_Data(controller_ID, ep_num, app_buff,size);
	#if IMPLEMENT_QUEUING
        	}
    	}
    	else /* bin is full */
    	{
        	error = USBERR_DEVICE_BUSY; 
    	}    
	#endif 
    
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_MSC_LBA_Transfer
 *
 * @brief 
 *
 * @param controller_ID:     To identify the controller   
 * @param direction       :   transfer direction
 * @param lba_info_ptr    :   buffer to send
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/
uint_8 USB_MSC_LBA_Transfer
(
	uint_8 controller_ID,
	boolean direction,
	PTR_LBA_INFO_STRUCT lba_info_ptr
)
{
	uint_8 error;
	LBA_APP_STRUCT lba_data;	
	
	if((!((lba_info_ptr->starting_lba<g_msc.device_info.total_lba_device_supports)&&
    	(lba_info_ptr->lba_transfer_num <= (g_msc.device_info.total_lba_device_supports - 
    	lba_info_ptr->starting_lba)))) || (g_msc.param_callback == NULL))
	{
		/* host trying to access region beyond MASS STORAGE SPACE 
		   Or no param_callback is registered */
    	return(uint_8)((direction?USBERR_TX_FAILED:USBERR_RX_FAILED));
	}

	g_transfer_remaining = lba_info_ptr->lba_transfer_num * 
	  g_msc.device_info.length_of_each_lba_of_device;				
	g_current_offset = lba_info_ptr->starting_lba * 
	  g_msc.device_info.length_of_each_lba_of_device;
	
	lba_data.offset = g_current_offset;

	if(direction == USB_SEND)
    {
  		lba_data.size = (g_transfer_remaining > MSC_SEND_DATA_BUFF_SIZE) ? 
			MSC_SEND_DATA_BUFF_SIZE : g_transfer_remaining; /* whichever is smaller */
		lba_data.buff_ptr = g_msc.msc_lba_send_buff;
	  	
	  	g_msc.param_callback(controller_ID, USB_MSC_DEVICE_READ_REQUEST,
	  		(void*)&lba_data);

    	error = USB_MSC_Bulk_Send_Data(controller_ID,lba_data.buff_ptr,lba_data.size);
    }
    else
    {
  		lba_data.size = (g_transfer_remaining > MSC_RECV_DATA_BUFF_SIZE) ? 
			MSC_RECV_DATA_BUFF_SIZE : g_transfer_remaining; /* whichever is smaller */
		lba_data.buff_ptr = g_msc.msc_lba_recv_buff;
	    error = USB_MSC_Bulk_Recv_Data(&controller_ID,lba_data.buff_ptr,lba_data.size);	
    }	    		
    return error;
}

/* EOF */
