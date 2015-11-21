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
 * @file usb_cdc.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains USB stack CDC class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_CDC_H
#define _USB_CDC_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_descriptor.h"
#include "usb_class.h"
#include "usb_cdc_pstn.h"
#include "usb_devapi.h"
#ifdef COMPOSITE_DEV
#include "usb_composite.h"
#endif

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Class specific request Codes */
#define SEND_ENCAPSULATED_COMMAND       (0x00)
#define GET_ENCAPSULATED_RESPONSE       (0x01)
#define SET_COMM_FEATURE                (0x02)
#define GET_COMM_FEATURE                (0x03)
#define CLEAR_COMM_FEATURE              (0x04)
#define SET_AUX_LINE_STATE              (0x10)
#define SET_HOOK_STATE                  (0x11)
#define PULSE_SETUP                     (0x12)
#define SEND_PULSE                      (0x13)
#define SET_PULSE_TIME                  (0x14)
#define RING_AUX_JACK                   (0x15)
#define SET_LINE_CODING                 (0x20)
#define GET_LINE_CODING                 (0x21)
#define SET_CONTROL_LINE_STATE          (0x22)
#define SEND_BREAK                      (0x23)
#define SET_RINGER_PARAMS               (0x30)
#define GET_RINGER_PARAMS               (0x31)
#define SET_OPERATION_PARAM             (0x32)
#define GET_OPERATION_PARAM             (0x33)
#define SET_LINE_PARAMS                 (0x34)
#define GET_LINE_PARAMS                 (0x35)
#define DIAL_DIGITS                     (0x36)
#define SET_UNIT_PARAMETER              (0x37)
#define GET_UNIT_PARAMETER              (0x38)
#define CLEAR_UNIT_PARAMETER            (0x39)
#define GET_PROFILE                     (0x3A)
#define SET_ETHERNET_MULTICAST_FILTERS  (0x40)
#define SET_ETHERNET_POW_PATTER_FILTER  (0x41)
#define GET_ETHERNET_POW_PATTER_FILTER  (0x42)
#define SET_ETHERNET_PACKET_FILTER      (0x43)
#define GET_ETHERNET_STATISTIC          (0x44)
#define SET_ATM_DATA_FORMAT             (0x50)
#define GET_ATM_DEVICE_STATISTICS       (0x51)
#define SET_ATM_DEFAULT_VC              (0x52)
#define GET_ATM_VC_STATISTICS           (0x53)
#define MDLM_SPECIFIC_REQUESTS_MASK     (0x7F)

/* Class Specific Notification Codes */
#define NETWORK_CONNECTION_NOTIF        (0x00)
#define RESPONSE_AVAIL_NOTIF            (0x01)
#define AUX_JACK_HOOK_STATE_NOTIF       (0x08)
#define RING_DETECT_NOTIF               (0x09)
#define SERIAL_STATE_NOTIF              (0x20)
#define CALL_STATE_CHANGE_NOTIF         (0x28)
#define LINE_STATE_CHANGE_NOTIF         (0x29)
#define CONNECTION_SPEED_CHANGE_NOTIF   (0x2A)
#define MDLM_SPECIFIC_NOTIF_MASK        (0x5F)

/* Events to the Application */ /* 0 to 4 are reserved for class events */
#define USB_APP_CDC_CARRIER_DEACTIVATED   (0x21)
#define USB_APP_CDC_CARRIER_ACTIVATED     (0x22)

/* other macros */
#define NOTIF_PACKET_SIZE             (0x08)
#define NOTIF_REQUEST_TYPE            (0xA1)

/* macros for queuing */
#define MAX_QUEUE_ELEMS  (4)

#if CIC_NOTIF_ELEM_SUPPORT
#define CIC_SEND_ENDPOINT       CIC_NOTIF_ENDPOINT
#endif

#if DIC_ISOCHRONOUS_SETTING
   #define  DIC_SEND_ENDPOINT  DIC_ISO_IN_ENDPOINT
   #define  DIC_RECV_ENDPOINT  DIC_ISO_OUT_ENDPOINT
#else
   #define  DIC_SEND_ENDPOINT  DIC_BULK_IN_ENDPOINT
   #define  DIC_RECV_ENDPOINT  DIC_BULK_OUT_ENDPOINT
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
#ifndef COMPOSITE_DEV
typedef struct _app_data_struct
{
    uint_8_ptr      data_ptr;       /* pointer to buffer */
    USB_PACKET_SIZE data_size;      /* buffer size of endpoint */
}APP_DATA_STRUCT;
#endif

/* structure to hold a request in the endpoint queue */
typedef struct _usb_class_cdc_queue
{
    uint_8 controller_ID;       /* Controller ID */
    uint_8 channel;             /* Endpoint Number */
    APP_DATA_STRUCT app_data;   /* Application Data Structure */
}USB_CLASS_CDC_QUEUE, *PTR_USB_CLASS_CDC_QUEUE;

/* USB class cdc endpoint data */
typedef struct _usb_class_cdc_endpoint
{
    uint_8 endpoint; /* endpoint num */
    uint_8 type;     /* type of endpoint (interrupt, bulk or isochronous) */
    uint_8 bin_consumer;/* the num of queued elements */
    uint_8 bin_producer;/* the num of de-queued elements */
    USB_CLASS_CDC_QUEUE queue[MAX_QUEUE_ELEMS]; /* queue data */
}USB_CLASS_CDC_ENDPOINT;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Class_CDC_Init (
	uint_8    		   		controller_ID,       /* [IN] Controller ID */
	USB_CLASS_CALLBACK 		cdc_class_callback,  /* [IN] CDC Class Callback */
	USB_REQ_FUNC       		vendor_req_callback, /* [IN] Vendor Request Callback */
	USB_CLASS_CALLBACK 		pstn_callback,       /* [IN] PSTN Callback */
	uint_8            		bVregEn              /* Enables or disables internal regulator */
);

#ifdef COMPOSITE_DEV
extern uint_8 USB_CDC_Other_Requests(uint_8 controller_ID,
                          USB_SETUP_STRUCT * setup_packet,
                          uint_8_ptr *data,
                          USB_PACKET_SIZE *size);
#endif

extern uint_8 USB_Class_CDC_DeInit 
(
    uint_8 controller_ID              
); 

extern uint_8 USB_Class_CDC_Send_Data (
    uint_8           controller_ID,
    uint_8           ep_num,
    uint_8_ptr       buff_ptr,
    USB_PACKET_SIZE  size
);

#if CIC_NOTIF_ELEM_SUPPORT
#define USB_Class_CDC_Interface_CIC_Send_Data(a,b,c)  \
    USB_Class_CDC_Send_Data(a,CIC_SEND_ENDPOINT,b,c)
#endif

#define USB_Class_CDC_Interface_DIC_Send_Data(a,b,c)  \
    USB_Class_CDC_Send_Data(a,DIC_SEND_ENDPOINT,b,c)
#define USB_Class_CDC_Interface_DIC_Recv_Data(a,b,c)  \
	_usb_device_recv_data(a,DIC_RECV_ENDPOINT,b,c)
#define USB_Class_CDC_Interface_DIC_Get_Send_Buffer(a,b,c)  \
	_usb_device_get_send_buffer(a,DIC_SEND_ENDPOINT,b,c)

#define USB_Class_CDC_Periodic_Task     USB_Class_Periodic_Task

#endif
