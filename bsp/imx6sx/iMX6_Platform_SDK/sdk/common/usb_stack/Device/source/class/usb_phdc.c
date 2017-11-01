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
 * @file usb_phdc.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack PHDC layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"          /* for EnableInterrupts macro */
#include <string.h>
#include "usb_phdc.h"       /* USB PHDC Class Header File */
#include "usb_devapi.h"     /* USB device Header File */

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "exceptions.h"
#endif
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
/****************************************************************************
 * Local Variables
 ****************************************************************************/
/* PHDC Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_phdc_class_callback;
/* PHDC Class Vendor Callback Function Pointer */
static USB_REQ_FUNC       g_vendor_req_callback;
/* PHDC endpoint info array */
static USB_CLASS_PHDC_ENDPOINT_DATA g_phdc_endpoint_data;
/* used to store a bit map of the active endpoints */
static uint_16 g_phdc_ep_has_data;

#if USB_METADATA_SUPPORTED
/* Pointer to metadata preamble */
static PTR_USB_META_DATA_MSG_PREAMBLE g_meta_data_msg_preamble;
/* used to store whether meta-data feature is active or not */
static boolean g_phdc_metadata;
/* string used to give preamble verifiability */
static const char msg_preamble_signature[] = "PhdcQoSSignature";
#endif
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests(uint_8 controller_ID,
                                    USB_SETUP_STRUCT*setup_packet,
                                    uint_8_ptr *data,
                                    USB_PACKET_SIZE *size);
#endif
static void USB_Class_PHDC_Event(uint_8 controller_ID,
                                    uint_8 event,
                                    void * value);
static void USB_Class_PHDC_TxEndpoint_InitQueue(USB_CLASS_PHDC_TX_ENDPOINT *ep_tx);
static void USB_Class_PHDC_Stall_Endpoint(uint_8 controller_ID,
                                          uint_8 ep_num,
                                          uint_8 direction);
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#pragma CODE_SEG DEFAULT
#endif
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Event
 *
 * @brief Initializes non control endpoints
 *
 * @param controller_ID      : Controller ID
 * @param event              : Event notified by the layer below
 * @param value              : Pointer to configuration Value
 *
 * @return                         : None
 ******************************************************************************
 * Initializes non control endpoints when Enumeration complete event is
 * received.
 *****************************************************************************/
static void USB_Class_PHDC_Event (
    uint_8 controller_ID, /* [IN] Controller ID */
    uint_8 event,         /* [IN] Event notified by the layer below */
    void * value          /* [IN] Pointer to configuration Value */
)
{
    uint_8 ep_count;
    USB_EP_STRUCT ep_struct;
    uint_8 index_num = 0;
    
#ifdef COMPOSITE_DEV
    uint_8 count;
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;   
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);    
    for(count = 0; count < dev_arc_ptr->cl_count; count++)
    {
        dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
        /* Initializes sub_classes */
        if(dev_class_ptr->class_type == 0x0F/*PHDC_CC*/)
            break;
        index_num +=dev_class_ptr->value[0];
    }   
#endif         

    if(event == USB_APP_ENUM_COMPLETE) /* if enum is complete initialize
                                          non-control endpoints */
    {
	    /* deinitialize all RECV endpoints in case they were initialized */
	    for(ep_count = g_phdc_endpoint_data.count_rx; 
	          ep_count > index_num; ep_count--) 
	    {   
		    ep_struct.ep_num = 
		        g_phdc_endpoint_data.ep_rx[ep_count - 1].endpoint;
		    (void)_usb_device_deinit_endpoint(&controller_ID,
		        ep_struct.ep_num, USB_RECV);
	    }        
        
        /* initialize all receive endpoints */
        for(ep_count = index_num; ep_count < g_phdc_endpoint_data.count_rx; ep_count++)
        {
            USB_CLASS_PHDC_RX_ENDPOINT *phdc_rx_endpoint = &g_phdc_endpoint_data.ep_rx[ep_count];
            
            /* initialize ep_struct */
            ep_struct.ep_num = phdc_rx_endpoint->endpoint;
            ep_struct.size = phdc_rx_endpoint->size;
            ep_struct.type = phdc_rx_endpoint->type;
            ep_struct.direction = USB_RECV;

            /* intialize endpoint */
            (void)_usb_device_init_endpoint(&controller_ID, ep_struct.ep_num, 
            		ep_struct.size, ep_struct.direction, ep_struct.type, FALSE); //testing

            /* set endpt status as idle in the device layer */
            (void)_usb_device_set_status(&controller_ID,
                (uint_8)(USB_STATUS_ENDPOINT |
                g_phdc_endpoint_data.ep_rx[ep_count].endpoint|
                (ep_struct.direction <<
                USB_COMPONENT_DIRECTION_SHIFT)),
                USB_STATUS_IDLE);
            phdc_rx_endpoint->buff_ptr = NULL;
            phdc_rx_endpoint->buffer_size = 0;
            phdc_rx_endpoint->cur_offset = 0;
            phdc_rx_endpoint->transfer_size = 0;

        }

        /* deinitialize all SEND endpoints in case they were initialized */
	    for(ep_count = g_phdc_endpoint_data.count_tx; ep_count > index_num; ep_count--)
	    {   
	        ep_struct.ep_num = 
	            g_phdc_endpoint_data.ep_tx[ep_count - 1].endpoint;
	        (void)_usb_device_deinit_endpoint(&controller_ID,
	            ep_struct.ep_num, USB_SEND);
	    }
 		    
        /* initialize all transmit endpoints */
        for(ep_count = index_num; ep_count < g_phdc_endpoint_data.count_tx; ep_count++)
        {
            USB_CLASS_PHDC_TX_ENDPOINT *ep_tx_ptr = &g_phdc_endpoint_data.ep_tx[ep_count];
            
            /* initialize ep_struct */
            ep_struct.ep_num = ep_tx_ptr->endpoint;
            ep_struct.size = ep_tx_ptr->size;
            ep_struct.type = ep_tx_ptr->type;
            ep_struct.direction = USB_SEND;

            /* intialize endpoint */
            (void)_usb_device_init_endpoint(&controller_ID, ep_struct.ep_num, 
            		ep_struct.size, ep_struct.direction, ep_struct.type, FALSE);

            /* Initialize the transmit queue (producer,consumer,transfer_size and current_offset to zero)
             * for transmit endpoints 
             */
            USB_Class_PHDC_TxEndpoint_InitQueue(ep_tx_ptr); 

            /* set endpt status as idle in the device layer */
            (void)_usb_device_set_status(&controller_ID,
                (uint_8)(USB_STATUS_ENDPOINT |
                ep_tx_ptr->endpoint|
                (ep_struct.direction <<
                USB_COMPONENT_DIRECTION_SHIFT)),
                USB_STATUS_IDLE);
        }
    }
    else 
    {      
     if(event == USB_APP_BUS_RESET)
     {
        /* Initialize the transmit queue (producer,consumer,transfer_size and current_offset to zero)
         * for transmit endpoints 
         */
        for(ep_count = index_num; ep_count < g_phdc_endpoint_data.count_tx; ep_count++)
        {
            USB_Class_PHDC_TxEndpoint_InitQueue(&g_phdc_endpoint_data.ep_tx[ep_count]);            
        }

     }
    }
    
    
    if(g_phdc_class_callback != NULL)
    {
        /* notify the application of the event */
        g_phdc_class_callback(controller_ID, event, value);
    }
}


/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_TxEndpoint_InitQueue
 *
 * @brief The funtion initializes the transmit queue of a Tx Endpoint
 *
 * @param ep_tx              : Pointer to the Tx Endpoint structure
 *
 * @return                   : NONE
 *
 ******************************************************************************
 * Initializes the Tx Endpoint Queue
 *****************************************************************************/
static void USB_Class_PHDC_TxEndpoint_InitQueue(USB_CLASS_PHDC_TX_ENDPOINT *ep_tx) 
{
  if(ep_tx != NULL) 
  {
   ep_tx->bin_consumer = 0;
   ep_tx->bin_producer = 0;
   ep_tx->transfer_size = 0;
   ep_tx->current_offset = 0;
  }
}
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Stall_Endpoint
 *
 * @brief The funtion calls the lower layer API to stall the endpoint
 *
 * @param controller_ID      : Controller ID
 * @param ep_num             : Endpoint number
 * @param direction          : Endpoint Direction
 *
 * @return                   :  NONE
 *
 ******************************************************************************
 * Stalls the input endpoint
 *****************************************************************************/
static void USB_Class_PHDC_Stall_Endpoint (
    uint_8 controller_ID,  /* [IN] Controller ID */
    uint_8 ep_num,         /* [IN] Endpoint number */
    uint_8 direction       /* [IN] Endpoint Direction */
)
{
    DisableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_dis();
    #endif			
    /* Empty Queue */
    if(direction == USB_SEND)
    {
        /* for send endpoints */
    }
    else
    {
        /* Cancel any pending Transfer  on the input endpoint number */
        (void)_usb_device_cancel_transfer(&controller_ID, ep_num, direction);
    }
    /* call lower layer api to stall endpoint */
    (void)_usb_device_set_status(&controller_ID, (uint_8)(USB_STATUS_ENDPOINT |
        ep_num | (direction << USB_COMPONENT_DIRECTION_SHIFT)),
        USB_STATUS_STALLED);
    EnableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_en();
    #endif		
    return;
}


/**************************************************************************//*!
 *
 * @name  USB_Other_Requests
 *
 * @brief The funtion provides flexibilty to add class and vendor specific
 *        requests
 *
 * @param controller_ID       : Controller ID
 * @param setup_packet        : Setup packet received
 * @param data                : Data to be send back
 * @param size                : Size to be returned
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * Handles PHDC Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
#ifndef COMPOSITE_DEV
static uint_8 USB_Other_Requests 
#else
uint_8 USB_Phdc_Other_Requests
#endif
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    boolean valid_interface = 0;
    if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_CLASS)
    {
        /*class request so handle it here */
        *size = 0;
        status = USB_OK;

        valid_interface = USB_Desc_Valid_Interface(controller_ID,
            (uint_8)setup_packet->index);
        if(valid_interface == FALSE)
        {
            status = USBERR_INVALID_REQ_TYPE;
            return status;
        }

        switch(setup_packet->request)
        {
            case SET_FEATURE_REQUEST:
            case CLEAR_FEATURE_REQUEST:
            {
#if USB_METADATA_SUPPORTED
                /* set/clear meta data feature */
                g_phdc_metadata = (boolean)((setup_packet->request &
                    USB_SET_REQUEST_MASK) >> 1);

                /* inform the application that feature has changed */
                g_phdc_class_callback(controller_ID,
                    USB_APP_FEATURE_CHANGED, (void*)(&g_phdc_metadata));
#else
                /* invalid request */
                status = USBERR_INVALID_REQ_TYPE;
#endif
            break;
            }
            case GET_STATUS_REQUEST:
            {
                /* 
                   implement get status request to get which endpoint has data 
                */
                if( setup_packet->value != 0 ) 
                {
                  status = USBERR_INVALID_REQ_TYPE;
                  break;
                }
                *data = (uint_8_ptr)(&g_phdc_ep_has_data);
                *size = (USB_PACKET_SIZE)setup_packet->length;
                break;
            }
            default:
                status = USBERR_INVALID_REQ_TYPE;
        }
    }
    else if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_VENDOR)
    {    
        /* vendor specific request  */
        if(g_vendor_req_callback != NULL)
        {
            status = g_vendor_req_callback(controller_ID, setup_packet,
                data,size);
        }
    }

    return status;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Endpoint_Service
 *
 * @brief Called upon a completed endpoint (non-control) transfer
 *
 * @param event     : Pointer to USB Event Structure
 *
 * @return  None
 ******************************************************************************
 * This function is called when a transfer (send or recv) completes on a
 * non control endpoint
 *****************************************************************************/
void USB_Class_PHDC_Endpoint_Service (
    PTR_USB_DEV_EVENT_STRUCT event  /* [IN] Pointer to USB Event Structure */
)
{
    uint_8 index;
    uint_8 transfers_left;
    uint_8 producer, consumer;
    USB_APP_EVENT_SEND_COMPLETE event_send_complete;
    USB_APP_EVENT_DATA_RECEIVED event_data_received;
#if USB_METADATA_SUPPORTED
    uint_8 meta_data_packet;
    USB_APP_EVENT_METADATA_PARAMS metadata_params;
#endif
    USB_CLASS_PHDC_QOS_BIN qos_bin;

    if(event->direction == USB_SEND)
    {
        USB_CLASS_PHDC_TX_ENDPOINT *phdc_tx_endpoint;
        
        /* get the index for the corresponding endpoint(channel) */
        for(index = 0; index < PHDC_TX_ENDPOINTS; index++)
        {
            if(g_phdc_endpoint_data.ep_tx[index].endpoint == event->ep_num)
            break;
        }
        
        phdc_tx_endpoint = &g_phdc_endpoint_data.ep_tx[index];
        
        /* initialize producer with the num of queued transfers */
        producer = phdc_tx_endpoint->bin_producer;
        /* initialize consumer with the num of de-queued transfers */
        consumer = phdc_tx_endpoint->bin_consumer;

        /* 
           if there are no errors de-queue the queue and decrement 
           the no. of transfers left, else send the same data again 
        */
        
        if(event->errors == 0)
        {
            phdc_tx_endpoint->current_offset += event->len;
            
            if((phdc_tx_endpoint->current_offset == 
                phdc_tx_endpoint->transfer_size) &&
                (event->len != 0))
            {
                if(phdc_tx_endpoint->transfer_size % phdc_tx_endpoint->size == 0) 
                {
                    /* send Zero Byte Data */
                    (void)USB_Class_Send_Data(event->controller_ID, event->ep_num,
                        NULL, 0);   
                    return; 
                }
            }
            
            /* de-queue the queue */
            phdc_tx_endpoint->bin_consumer++;
        }

        consumer = phdc_tx_endpoint->bin_consumer;

        /* get the qos information of the next transfer */
        qos_bin = phdc_tx_endpoint->qos_bin[consumer % MAX_QOS_BIN_ELEMS];
        if(consumer != producer)
        {
            /*if bin is not empty */
#if USB_METADATA_SUPPORTED
            if(qos_bin.meta_data == TRUE)
            {
                /* 
                   initialize current_qos of the transfers 
                   that follow the meta data packet 
                */
                phdc_tx_endpoint->current_qos = qos_bin.qos;
            }
#endif
            /* Get new transfer Size from already queued Transfer */
            if(phdc_tx_endpoint->current_offset == 
                phdc_tx_endpoint->transfer_size) 
            {
                USB_CLASS_PHDC_XFER_SIZE xfer_size;
                
                xfer_size.in_buff = event->buffer_ptr;
                xfer_size.in_size = event->len;
                xfer_size.transfer_size = 0;
                xfer_size.direction = USB_SEND;
#if USB_METADATA_SUPPORTED
                xfer_size.meta_data_packet = qos_bin.meta_data;
#endif               
                g_phdc_class_callback(event->controller_ID, 
                    USB_APP_GET_TRANSFER_SIZE, (void*)(&xfer_size));

                phdc_tx_endpoint->transfer_size = xfer_size.transfer_size;
                phdc_tx_endpoint->current_offset = 0;
                
            }
            /* send data */
            (void)USB_Class_Send_Data(qos_bin.controller_ID, qos_bin.channel,
                qos_bin.app_buff, qos_bin.size);
        }
        else /* bin is empty */
        {
            /*set endpoint bin as non active */
            g_phdc_ep_has_data &= ~(BYTE_SWAP16(1 << event->ep_num));
        }

        /* Set transfer_size and current_offset to 0 */
        phdc_tx_endpoint->transfer_size = 0;
        phdc_tx_endpoint->current_offset = 0;

        /* Set the USB_APP_EVENT_SEND_DATA structure */
        event_send_complete.qos = phdc_tx_endpoint->qos;
        event_send_complete.buffer_ptr = event->buffer_ptr;
        event_send_complete.size = event->len;

        /* notify the application of the send complete */
        g_phdc_class_callback(event->controller_ID, USB_APP_SEND_COMPLETE,
            (void*)(&event_send_complete));
    }
    else
    {
        /* direction is USB_RECV */

        USB_CLASS_PHDC_RX_BUFF rx_buff;
        USB_CLASS_PHDC_XFER_SIZE xfer_size;
        USB_PHDC_ERROR_STRUCT usb_phdc_error_struct;
        USB_CLASS_PHDC_RX_ENDPOINT *phdc_rx_endpoint;
        /* get the index for the corressponding endpoint */
        for(index = 0; index < PHDC_RX_ENDPOINTS; index++)
        {
            if(g_phdc_endpoint_data.ep_rx[index].endpoint == event->ep_num)
            break;
        }
        phdc_rx_endpoint = &g_phdc_endpoint_data.ep_rx[index];
        

        /* if there is an error notify the application of the error and
           return */
        if(event->errors != 0)
        {
            usb_phdc_error_struct.error_code = (USB_PHDC_ERROR)event->errors;
            usb_phdc_error_struct.qos = phdc_rx_endpoint->qos;
            
            phdc_rx_endpoint->buffer_size = 0;
            phdc_rx_endpoint->buff_ptr = NULL;
            phdc_rx_endpoint->transfer_size = 0;
            phdc_rx_endpoint->cur_offset = 0;
            

            /* notify the application of the error */
            g_phdc_class_callback(event->controller_ID, USB_APP_ERROR,
                (void*)(&usb_phdc_error_struct));

            return;
        }

        transfers_left = phdc_rx_endpoint->transfers_left;

        if(phdc_rx_endpoint->transfer_size == 0)
        {
#if USB_METADATA_SUPPORTED
            /* 
               in case of meta data packet, the packet is received
               as a short packet, so will not have to recv another packet to
               complete this transaction. Hence value of meta_data_packet
               variable will be valid at line no. 445 
             */

            /* 
               compare the received signature with the string for preamble
               verifiability. if meta_data_packet = 0(both signatures match)
               the incoming packet is a meta data 
            */
            if(g_phdc_metadata == TRUE)
            {
                boolean logical_meta_data_packet, logical_trans_left;
                meta_data_packet = (uint_8)strncmp(event->buffer_ptr, 
                    msg_preamble_signature, METADATA_PREAMBLE_SIGNATURE);

                logical_trans_left = (boolean)(transfers_left ? 1 : 0);
                logical_meta_data_packet = (boolean)(meta_data_packet ? 1 : 0);

                if((logical_trans_left ^ logical_meta_data_packet) == TRUE)
                {
                    /* if num of transfers is zero and the packet is
                    not meta data msg preamble, or if trasfers left
                    is non zero and meta data packet comes, error occurs*/
                    usb_phdc_error_struct.qos = phdc_rx_endpoint->qos;
                    if(logical_trans_left == TRUE)
                    {
                        usb_phdc_error_struct.error_code =
                            USB_PHDC_METADATA_RECEIVED_NOT_EXPECTED;
                    }
                    else
                    {
                        usb_phdc_error_struct.error_code =
                            USB_PHDC_METADATA_EXPECTED_NOT_RECEIVED;
                    }
                    /* stall endpoint */
                    USB_Class_PHDC_Stall_Endpoint(event->controller_ID,
                        event->ep_num, event->direction);

                    /* when complete packet is received
                       reset the buffer_size and buff_ptr */
                    phdc_rx_endpoint->buffer_size = 0;
                    phdc_rx_endpoint->buff_ptr = NULL;
                    phdc_rx_endpoint->cur_offset = 0;
                    phdc_rx_endpoint->transfer_size = 0;

                    /* notify the application of the error*/
                    g_phdc_class_callback(event->controller_ID,USB_APP_ERROR,
                        (void*)(&usb_phdc_error_struct));
                    
                    return;

                }

                rx_buff.meta_data_packet = (boolean)!meta_data_packet;
            }
            else
            {
                rx_buff.meta_data_packet = FALSE;
            }
#endif
            xfer_size.in_buff = event->buffer_ptr;
            xfer_size.in_size = event->len;
            xfer_size.direction = USB_RECV;
            xfer_size.transfer_size = 0;
#if USB_METADATA_SUPPORTED
            xfer_size.meta_data_packet = rx_buff.meta_data_packet;
#endif            
            g_phdc_class_callback(event->controller_ID, 
                USB_APP_GET_TRANSFER_SIZE, (void*)(&xfer_size));

            phdc_rx_endpoint->transfer_size = xfer_size.transfer_size;
            phdc_rx_endpoint->cur_offset = 0;
        } 

        /* Increment Current Offset */
        phdc_rx_endpoint->cur_offset += event->len;
        if((phdc_rx_endpoint->cur_offset < phdc_rx_endpoint->transfer_size) &&
        (event->len % phdc_rx_endpoint->size == 0))
        {
            rx_buff.in_buff = event->buffer_ptr;
            rx_buff.in_size = event->len;
            rx_buff.out_size = 0;
            rx_buff.out_buff = NULL;
            rx_buff.transfer_size = phdc_rx_endpoint->transfer_size;
            rx_buff.qos = phdc_rx_endpoint->qos;
            /* Callback application to copy data buffer */
            g_phdc_class_callback(event->controller_ID, USB_APP_GET_DATA_BUFF,
                (void*)(&rx_buff));
                
            return;
            
        }

        if((phdc_rx_endpoint->cur_offset >= phdc_rx_endpoint->transfer_size) ||
            (event->len % phdc_rx_endpoint->size != 0))
        {
            /* Check for Zero Byte Receive */
            if((phdc_rx_endpoint->transfer_size % phdc_rx_endpoint->size == 0) 
                && (event->len != 0))
            {
                (void)_usb_device_recv_data(&(event->controller_ID), event->ep_num, NULL, 0);
                return; 
            }
             /* Complete Data Packet is received */
#if USB_METADATA_SUPPORTED
            /* 
                Message Data Preamble is received in first packet call 
                so event->Buffer_ptr is valid
            */
            g_meta_data_msg_preamble =
                (PTR_USB_META_DATA_MSG_PREAMBLE)event->buffer_ptr;

            /* check whether transfers are left. we check for meta data only
             when number of transfers left is zero */
            if((g_phdc_metadata == FALSE) || (transfers_left != 0 &&
                meta_data_packet !=0))
            {
                if(g_phdc_metadata == TRUE)
                {
                    phdc_rx_endpoint->transfers_left =
                        (uint_8)(transfers_left - 1);
                }
                /* set the data received structure */
                event_data_received.qos = phdc_rx_endpoint->qos;
                event_data_received.buffer_ptr = event->buffer_ptr;
                event_data_received.size = event->len;
                event_data_received.transfer_size = 
                    phdc_rx_endpoint->transfer_size;
                /* when complete packet is received
                   reset the buffer_size and buff_ptr */
                phdc_rx_endpoint->buffer_size = 0;
                phdc_rx_endpoint->buff_ptr = NULL;
                phdc_rx_endpoint->cur_offset = 0;
                phdc_rx_endpoint->transfer_size = 0;

                /* notify the application that receive data is complete */
                g_phdc_class_callback(event->controller_ID,
                    USB_APP_DATA_RECEIVED, (void*)(&event_data_received));
            }
            else if((transfers_left == 0 ) && (meta_data_packet == 0))
            {   
                /* 
                   if number of transfers left is zero and the packet is meta
                   data msg preamble initialize the endpoint data structure
                   from the meta data msg preamble data structure 
                */

                if(!g_meta_data_msg_preamble->num_tfr ||
                    !g_meta_data_msg_preamble->qos ||
                    (!(phdc_rx_endpoint->qos &
                    g_meta_data_msg_preamble->qos)) ||
                    /* endpoint does not support this qos */
                    ( (g_meta_data_msg_preamble->qos &
                    (g_meta_data_msg_preamble->qos - 1))  ) )
                    /* multiple qos set */
                {
                    usb_phdc_error_struct.error_code =
                        USB_PHDC_CORRUPT_METADATA_PACKET_RECEIVED;
                    usb_phdc_error_struct.qos = phdc_rx_endpoint->qos;
                    /* stall endpoint */
                    USB_Class_PHDC_Stall_Endpoint(event->controller_ID,
                        event->ep_num, event->direction);

                    /* when complete packet is received
                       reset the buffer_size and buff_ptr */
                    phdc_rx_endpoint->buffer_size = 0;
                    phdc_rx_endpoint->buff_ptr = NULL;
                    phdc_rx_endpoint->cur_offset = 0;
                    phdc_rx_endpoint->transfer_size = 0;

                    /* if the packet is a meta data and num of transfers is
                       zero or qos is invalid return with an error */
                    /* notify the application of the error*/
                    g_phdc_class_callback(event->controller_ID, USB_APP_ERROR,
                        (void*)(&usb_phdc_error_struct));

                    return;
                }

                phdc_rx_endpoint->transfers_left =
                    g_meta_data_msg_preamble->num_tfr;
                phdc_rx_endpoint->current_qos =
                    g_meta_data_msg_preamble->qos;

                /* set the event phdc meta data params structure*/
                metadata_params.channel = event->ep_num;
                metadata_params.num_tfr = g_meta_data_msg_preamble->num_tfr;
                metadata_params.qos = g_meta_data_msg_preamble->qos;
                metadata_params.metadata_ptr =
                    &g_meta_data_msg_preamble->opaque_data[0];

                /* notify the application that meta data params has changed */
                g_phdc_class_callback(event->controller_ID,
                    USB_APP_META_DATA_PARAMS_CHANGED, 
                    (void*)(&metadata_params));

            }
#else
            /* set the data received structure */
            event_data_received.qos = phdc_rx_endpoint->qos;
            event_data_received.buffer_ptr = event->buffer_ptr;
            event_data_received.size = event->len;
            event_data_received.transfer_size = 
                phdc_rx_endpoint->transfer_size;
        
            /* when complete packet is received
               reset the buffer_size and buff_ptr */
            phdc_rx_endpoint->buffer_size = 0;
            phdc_rx_endpoint->buff_ptr = NULL;
            phdc_rx_endpoint->cur_offset = 0;
            phdc_rx_endpoint->transfer_size = 0;
            /* notify the application that receive data is complete */
            g_phdc_class_callback(event->controller_ID, USB_APP_DATA_RECEIVED,
                (void*)(&event_data_received));
#endif
        }

    }
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Recv_Data
 *
 * @brief This function is used by Application to receive data through PHDC 
 *        class
 *
 * @param controller_ID         : Controller ID
 * @param qos                   : Qos of the transfer
 * @param app_buff              : Buffer to send
 * @param size                  : Length of the transfer
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * This fucntion is used by Application to send data through PHDC class
 *****************************************************************************/
uint_8 USB_Class_PHDC_Recv_Data (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 qos,             /* [IN] Qos of the transfer */
    uint_8_ptr app_buff,    /* [IN] Buffer to receive */
    USB_PACKET_SIZE size    /* [IN] Length of the transfer */
)
{
    uint_8 rx_index;
    uint_8 status = USB_OK;
    USB_CLASS_PHDC_RX_ENDPOINT *phdc_rx_endpoint;
    /* get the index for the corressponding endpoint(channel) to receive data
     of desired qos */
    for(rx_index = 0; rx_index < PHDC_RX_ENDPOINTS; rx_index++)
    {
        if((g_phdc_endpoint_data.ep_rx[rx_index].qos & qos) !=0)
            break;
    }

    /* no channel supports the desired qos */
    if(rx_index == PHDC_RX_ENDPOINTS)
    {
        return USBERR_RX_FAILED;
    }
    phdc_rx_endpoint = &g_phdc_endpoint_data.ep_rx[rx_index];
    phdc_rx_endpoint->buffer_size = size;
    phdc_rx_endpoint->transfer_size = size;
    phdc_rx_endpoint->buff_ptr = app_buff;
    status = _usb_device_recv_data(&controller_ID, phdc_rx_endpoint->endpoint, app_buff,
        size);
    
    return status;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Send_Data
 *
 * @brief This fucntion is used by Application to send data through PHDC class
 *
 * @param controller_ID         : Controller ID
 * @param meta_data             : Packet is meta data or not
 * @param num_tfr               : Number of transfers following meta data packet
 * @param qos                   : Qos of the transfer
 * @param app_buff              : Buffer to send
 * @param size                  : Length of the transfer
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * This fucntion is used by Application to send data through PHDC class
 *****************************************************************************/
uint_8 USB_Class_PHDC_Send_Data (
    uint_8 controller_ID,   /* [IN] Controller ID */
    boolean meta_data,      /* [IN] Packet is meta data or not */
    uint_8 num_tfr,         /* [IN] Number of transfers
                                    following meta data packet */
    uint_8 qos,             /* [IN] Qos of the transfer */
    uint_8_ptr app_buff,    /* [IN] Buffer to send */
    USB_PACKET_SIZE size    /* [IN] Length of the transfer */
)
{
    uint_8 channel;
    uint_8 producer, consumer;
    uint_8 tx_index;
    uint_8 status = USB_OK;
    USB_CLASS_PHDC_TX_ENDPOINT *phdc_tx_endpoint;
    /* get the index for the corressponding endpoint(channel) to send data
     of desired qos */
    for(tx_index = 0; tx_index < PHDC_TX_ENDPOINTS; tx_index++)
    {
        if((g_phdc_endpoint_data.ep_tx[tx_index].qos & qos) != 0)
            break;
    }

    /* no channel supports the desired qos */
    if(tx_index == PHDC_TX_ENDPOINTS)
    {
        return USBERR_TX_FAILED;
    }
    phdc_tx_endpoint = &g_phdc_endpoint_data.ep_tx[tx_index];
    /* New APDU Transfer */
    if(phdc_tx_endpoint->transfer_size == 0)
    {
#if USB_METADATA_SUPPORTED
        /* if the packet to send is not as desired return with an error */
        if((((phdc_tx_endpoint->transfers_queued == 0) ||
          (phdc_tx_endpoint->type != USB_BULK_PIPE)) &&
          (meta_data == FALSE) && (g_phdc_metadata == TRUE)) ||
          ((g_phdc_metadata == FALSE) && (meta_data == TRUE)))

        {
            return USBERR_TX_FAILED;
        }
                    
        if(meta_data == TRUE)
        {
            /* Prepare Meta Data PReamble Packet based on input information */
            USB_META_DATA_MSG_PREAMBLE *metadata_preamble =
                (USB_META_DATA_MSG_PREAMBLE *) app_buff;

            if(size > phdc_tx_endpoint->size)
            {
                return USBERR_TX_FAILED;
            }

            /* 
               if num of transfers is zero &/or qos is zero or multiple qos
               bits are set, return with an error 
            */
            if( !num_tfr || !qos || (  (qos & (qos - 1))  ) )
            {
                return USBERR_TX_FAILED;
            }

            if(phdc_tx_endpoint->transfers_queued != 0)
            {
                return USBERR_TX_FAILED;
            }

            
            phdc_tx_endpoint->transfers_queued = (uint_8)
                (num_tfr + 1);
            /* Copy Meta Data Preamble Signature */
            (void)memcpy(metadata_preamble->signature, msg_preamble_signature,
                METADATA_PREAMBLE_SIGNATURE);
            metadata_preamble->num_tfr = num_tfr;
            metadata_preamble->version = METADATA_QOSENCODING_VERSION;
            metadata_preamble->qos = qos;
            metadata_preamble->opaque_data_size = (uint_8)(size - 
                METADATA_HEADER_SIZE);
        }
#endif

    }/* if(transfer_size == 0) */
    
    channel = phdc_tx_endpoint->endpoint;

    /* set channel active-- set bit map for
    the corressponding channel(endpoint)*/
    g_phdc_ep_has_data |= BYTE_SWAP16(1 << channel);

    /* initialize producer with the num of queued transfers */
    producer = phdc_tx_endpoint->bin_producer;
    /* initialize consumer with the num of de-queued transfers */
    consumer = phdc_tx_endpoint->bin_consumer;

    if((uint_8)(producer - consumer) != (uint_8)(MAX_QOS_BIN_ELEMS))
    {
        /* the bin is not full*/

        uint_8 queue_num = (uint_8)(producer % MAX_QOS_BIN_ELEMS);

        if(phdc_tx_endpoint->transfer_size == 0)
        {
            phdc_tx_endpoint->transfers_queued--;
        }

        /* put all send request parameters in the endpoint data structure */
        phdc_tx_endpoint->qos_bin[queue_num].controller_ID = controller_ID;
        phdc_tx_endpoint->qos_bin[queue_num].channel = channel;
        phdc_tx_endpoint->qos_bin[queue_num].meta_data = meta_data;
        phdc_tx_endpoint->qos_bin[queue_num].num_tfr = num_tfr;
        phdc_tx_endpoint->qos_bin[queue_num].qos = qos;
        phdc_tx_endpoint->qos_bin[queue_num].app_buff = app_buff;
        phdc_tx_endpoint->qos_bin[queue_num].size = size;

        /* increment producer bin by 1 -- queue the transfer */
        phdc_tx_endpoint->bin_producer = ++producer;

        if((uint_8)(producer - consumer) == (uint_8)1)
        {
            /* bin has only this packet to send */
            if(phdc_tx_endpoint->transfer_size == 0)
            {
                /* 
                    Get Total Transfer Size 
                    This is required for Bridges that send APDU fragmented
                */
                USB_CLASS_PHDC_XFER_SIZE xfer_size;
                
                xfer_size.in_buff = app_buff;
                xfer_size.in_size = size;
                xfer_size.transfer_size = 0;
                xfer_size.direction = USB_SEND;
#if USB_METADATA_SUPPORTED
                xfer_size.meta_data_packet = 
                    phdc_tx_endpoint->qos_bin[queue_num].meta_data;
#endif               
                g_phdc_class_callback(controller_ID, 
                    USB_APP_GET_TRANSFER_SIZE, (void*)(&xfer_size));

                phdc_tx_endpoint->transfer_size = xfer_size.transfer_size;
                phdc_tx_endpoint->current_offset = 0;
            }

#if USB_METADATA_SUPPORTED
            if(meta_data == TRUE)
            {
                /* initialize current_qos of the transfers that follow the
                meta data packet */
                phdc_tx_endpoint->current_qos = qos;
            }
#endif

            /* send the packet if there is no packet (other than this packet)
            in the queue */
            status = USB_Class_Send_Data(controller_ID,channel, app_buff,size);
        }

    }
    else /* bin is full */
    {
        /* return device is busy when the queue is full */
        status = USBERR_DEVICE_BUSY;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Init
 *
 * @brief The funtion initializes the Device and Controller layer
 *
 * @param controller_ID             : Controller ID
 * @param phdc_class_callback       : PHDC class callback
 * @param vendor_req_callback       : Vendor Request callback
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * This function initializes the PHDC Class layer and layers it is dependent on
 *****************************************************************************/
uint_8 USB_Class_PHDC_Init(
    uint_8 controller_ID,                   /* [IN] Controller ID */
    USB_CLASS_CALLBACK phdc_class_callback, /* [IN] PHDC class callback */
    USB_REQ_FUNC       vendor_req_callback  /* [IN] Vendor Request callback */
)
{
    uint_8 ep_count, count=0;
    uint_8 status = USB_OK, ep_num= 0,index_num = 0;

#ifdef COMPOSITE_DEV
    DEV_ARCHITECTURE_STRUCT_PTR dev_arc_ptr;
    CLASS_ARC_STRUCT_PTR dev_class_ptr;   
    dev_arc_ptr = (DEV_ARCHITECTURE_STRUCT *)USB_Desc_Get_Class_Architecture(controller_ID);    
    for(count = 0; count < dev_arc_ptr->cl_count; count++)
    {
        dev_class_ptr = (CLASS_ARC_STRUCT_PTR)dev_arc_ptr->value[count];
        /* Initializes sub_classes */
        ep_num = dev_class_ptr->value[0];
        if(dev_class_ptr->class_type == 0x0F/*PHDC_CC*/)
            break;
        index_num +=dev_class_ptr->value[0];
    }
/* get the endpoint info from the descriptor module */
    USB_CLASS_PHDC_CHANNEL_INFO* const info =
        (USB_CLASS_PHDC_CHANNEL_INFO*)USB_Desc_Get_Endpoints(controller_ID);
#else

    /* get the endpoint info from the descriptor module */
    USB_CLASS_PHDC_CHANNEL_INFO* const info =
        (USB_CLASS_PHDC_CHANNEL_INFO*)USB_Desc_Get_Endpoints(controller_ID);

    ep_num = info->count;
    /* initialize the device */
    status = _usb_device_init(controller_ID, NULL, (uint_8)((info->count) + 1), TRUE);

    if(status == USB_OK)
    {
        status = USB_Class_Init(controller_ID, USB_Class_PHDC_Event,
            USB_Other_Requests);
        if(status == USB_OK)
        {
#endif
            g_phdc_endpoint_data.count_rx = index_num;
            g_phdc_endpoint_data.count_tx = index_num;

            /* initialize endpoint data structure for all endpoints */
            for(ep_count = index_num; ep_count < ep_num+index_num; ep_count++)
            {
                if((info->channel[ep_count].direction == USB_RECV) &
                    (g_phdc_endpoint_data.count_rx < PHDC_RX_ENDPOINTS))
                {

                    count = g_phdc_endpoint_data.count_rx;

                    /* initialize endpoint data structure for recv endpoint */
                    g_phdc_endpoint_data.ep_rx[count].endpoint =
                            info->channel[ep_count].channel_num;
                    g_phdc_endpoint_data.ep_rx[count].type =
                            info->channel[ep_count].type;
                    g_phdc_endpoint_data.ep_rx[count].size =
                            info->channel[ep_count].size;
                    g_phdc_endpoint_data.ep_rx[count].qos =
                            info->channel[ep_count].qos;
                    g_phdc_endpoint_data.ep_rx[count].transfers_left = 0;
                    g_phdc_endpoint_data.ep_rx[count].current_qos =
                        INVALID_VAL;

                    /* register endpoint service on the endpoint*/
                    (void)_usb_device_register_service(controller_ID,
                        g_phdc_endpoint_data.ep_rx[count].endpoint,
                        USB_Class_PHDC_Endpoint_Service);
                    /* increment count_rx by 1 */
                    g_phdc_endpoint_data.count_rx++;

                }
                else if((info->channel[ep_count].direction == USB_SEND) &
                    (g_phdc_endpoint_data.count_tx < PHDC_TX_ENDPOINTS))
                {

                    count= g_phdc_endpoint_data.count_tx;

                    /* initialize endpoint data structure for send endpoint */
                    g_phdc_endpoint_data.ep_tx[count].endpoint =
                        (uint_8)info->channel[ep_count].channel_num;
                    g_phdc_endpoint_data.ep_tx[count].type =
                        (uint_8)info->channel[ep_count].type;
                    g_phdc_endpoint_data.ep_tx[count].size =
                        (USB_PACKET_SIZE)info->channel[ep_count].size;
                    g_phdc_endpoint_data.ep_tx[count].qos =
                        (uint_8)info->channel[ep_count].qos;
                    g_phdc_endpoint_data.ep_tx[count].current_qos =
                        (uint_8)INVALID_VAL;
                    g_phdc_endpoint_data.ep_tx[count].bin_consumer =
                        (uint_8)0x00;
                    g_phdc_endpoint_data.ep_tx[count].bin_producer =
                        (uint_8)0x00;
                    g_phdc_endpoint_data.ep_tx[count].transfers_queued = 0;
                    g_phdc_endpoint_data.ep_tx[count].transfer_size = 0;

                    /* register endpoint service on the endpoint*/
                    (void)_usb_device_register_service(controller_ID,
                        g_phdc_endpoint_data.ep_tx
                        [g_phdc_endpoint_data.count_tx].endpoint, 
                        USB_Class_PHDC_Endpoint_Service);

                    /* increment count_tx by 1 */
                    g_phdc_endpoint_data.count_tx++;

                }
            }

            /* set device state as powered */
            (void)_usb_device_set_status(&controller_ID, USB_STATUS_DEVICE_STATE,
                USB_STATE_POWERED);
#if USB_METADATA_SUPPORTED
            g_phdc_metadata = FALSE; /* metadata feature disabled */
#endif
            g_phdc_ep_has_data = 0; /* no endpoint has data */

            /* save the PHDC class callback pointer */
            g_phdc_class_callback = phdc_class_callback;

            /* save the vendor request callback pointer */
            g_vendor_req_callback = vendor_req_callback;
#ifndef COMPOSITE_DEV

        }
    }
#endif
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_DeInit
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
 *This function de-initializes the PHDC Class layer
 *****************************************************************************/
uint_8 USB_Class_PHDC_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status;
#ifdef COMPOSITE_DEV  
    UNUSED(controller_ID)
#endif  
    /* free the PHDC class callback pointer */
    g_phdc_class_callback = NULL;
    
    /* free the vendor request callback pointer */
    g_vendor_req_callback = NULL;
    
#ifndef COMPOSITE_DEV
    /* Call common class deinit function */
    status = USB_Class_DeInit(controller_ID);
    
    if(status == USB_OK)
    /* Call device deinit function */
    	status = _usb_device_deinit();
#endif    
    return status;
} 
